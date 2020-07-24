#include "Fleaman.h"

Fleaman::Fleaman(D3DXVECTOR2 position)
{
	this->x = position.x;
	this->y = position.y;
	this->firstPos = position;

	isStartAttack = false;
	isActive = false;
	isFirstJump = true;
	firstJumpStart = jumpOnGroundStart = attackStart = onGroundStart = 0;
	score = 200;
	health = 1;

	id = ID_FLEAMAN;
	SetState(FLEAMAN_STATE_PREATTACK);

	AddAnimation(ID_ANI_FLEAMAN_IDLE_RIGHT);
	AddAnimation(ID_ANI_FLEAMAN_IDLE_LEFT);
	AddAnimation(ID_ANI_FLEAMAN_PREATTACK);
	AddAnimation(ID_ANI_FLEAMAN_JUMP_RIGHT);
	AddAnimation(ID_ANI_FLEAMAN_JUMP_LEFT);
}


Fleaman::~Fleaman()
{
}

void Fleaman::Render()
{
	int ani = 0;

	switch (state)
	{
	case ENEMY_STATE_DIE:
		ani = ENEMY_ANI_HITTED;
		break;
	case ENEMY_STATE_IDLE:
		if (nx > 0)
			ani = FLEAMAN_ANI_IDLE_RIGHT;
		else
			ani = FLEAMAN_ANI_IDLE_LEFT;
		break;
	case ENEMY_STATE_ACTIVE:
	{
		if (nx < 0)
			ani = FLEAMAN_ANI_JUMP_RIGHT;
		else
			ani = FLEAMAN_ANI_JUMP_LEFT;
		break;
	}
	case FLEAMAN_STATE_PREATTACK:
		ani = FLEAMAN_ANI_PREATTACK;
		break;
	case FLEAMAN_STATE_ATTACK:
	{
		if (nx < 0)
			ani = FLEAMAN_ANI_JUMP_RIGHT;
		else
			ani = FLEAMAN_ANI_JUMP_LEFT;
		break;
	}
	default:
		break;
	}
	if (hitEffectStart > 0)
		ani = ENEMY_ANI_HITTED;
	animations[ani]->Render(x, y);
}

void Fleaman::Update(DWORD dt, vector<LPGAMEOBJECT> *nonGridObject, set<LPGAMEOBJECT> gridObject)
{
	float al, at, ar, ab;
	float bl, bt, br, bb;

	al = CGame::GetInstance()->GetCamPosX();
	at = CGame::GetInstance()->GetCamPosY();

	ar = al + SCREEN_WIDTH;
	ab = at + SCREEN_HEIGHT;

	GetBoundingBox(bl, bt, br, bb);

	RECT A, B;
	A = { long(al),long(at),long(ar),long(ab) };
	B = { long(bl),long(bt),long(br),long(bb) };

	if (!CGame::GetInstance()->IsColliding(A, B))
		return;

	CGameObject::Update(dt, nonGridObject, gridObject);
	vy += FLEAMAN_GRAVITY * dt;
	Simon* simon = Simon::GetInstance();
	vector<LPGAMEOBJECT> *realCoObjects;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	realCoObjects = new vector<LPGAMEOBJECT>;

	for (auto i : gridObject) {
		switch (i->GetId())
		{
		case ID_WALL:
			realCoObjects->push_back(i);
			break;
		default:
			break;
		}
	}

	// turn off collision when die 
	CalcPotentialCollisions(realCoObjects, coEvents);

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		//DebugOut(L"------No collision\n");
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		//DebugOut(L"----Fleaman ny: %d\n", ny);

		//x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		
		//DebugOut(L"--Fleaman vx, vy: %f/ %f\n", vx, vy);
		x += dx;

		//if (nx != 0) {
		//	vx = 0;
		//}
		if (ny < 0) {
			y += min_ty * dy + ny * 0.1f;
			vy = 0;
			SetState(ENEMY_STATE_IDLE);
		}
		else {
			y += dy;
		}
	}
	if (isFirstJump) {
		float sl, st, sr, sb;
		float fl, ft, fr, fb;

		simon->GetBoundingBox(sl, st, sr, sb);
		GetBoundingBox(fl, ft, fr, fb);

		if (abs(fl - sl) < FLEAMAN_ACTIVE_DISTANCE_WIDTH) {
			StartActive();
			//DebugOut(L"--After first active vx, vy: %f/ %f\n", vx, vy);
		}
	}
	if (!isFirstJump && isActive) {
		if (firstJumpStart > 0 && GetTickCount() - firstJumpStart > FLEAMAN_TIME_ATTACK) {
			firstJumpStart = 0;
			jumpOnGroundStart = GetTickCount();
			nx = -simon->GetNx();
			//DebugOut(L"nx first active: %d\n", nx);
		}
		if (jumpOnGroundStart && onGroundStart == 0) {
			SetState(ENEMY_STATE_ACTIVE);
			if (x < simon->GetX()) {
				nx = 1;
				vx = nx*vx;
			}
			if (x > simon->GetX()) {
				nx = -1;
				vx = nx*vx;
			}
			//DebugOut(L"----- vx, vy, nx: %f/ %f/ %d\n", vx, vy, nx);
			onGroundStart = GetTickCount();
		}
		if (jumpOnGroundStart && onGroundStart > 0 && GetTickCount() - onGroundStart > FLEAMAN_TIME_JUMP_ON_GROUND) {
			onGroundStart = 0;
			isStartAttack = true;
		}
		if (isStartAttack) {
			float sl, st, sr, sb;
			float fl, ft, fr, fb;

			simon->GetBoundingBox(sl, st, sr, sb);
			GetBoundingBox(fl, ft, fr, fb);

			RECT S, F;
			S = { long(sl), long(st), long(sr), long(sb) };
			F = { long(fl), long(ft), long(fr), long(fb) };

			if (CGame::GetInstance()->IsColliding(F, S)) {
				jumpOnGroundStart = 0;
				attackStart = GetTickCount();
				SetState(FLEAMAN_STATE_ATTACK);
				vx = nx * FLEAMAN_SPEED_X;
				//DebugOut(L"-----Attack vx, vy, nx: %f/ %f/ %d\n", vx, vy, nx);
			}
		}
		if (attackStart > 0 && GetTickCount() - attackStart > FLEAMAN_TIME_ATTACK) {
			attackStart = 0;
			isStartAttack = false;
			jumpOnGroundStart = GetTickCount();
		}
	}
	DWORD effectTimeCount = GetTickCount() - hitEffectStart;

	if (effectTimeCount > HIT_EFFECT_TIME && hitEffectStart > 0) {
		hitEffectStart = 0;
		state = STATE_DESTROYED;
	}
}

void Fleaman::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + FLEAMAN_BBOX_WIDTH;
	bottom = y + FLEAMAN_BBOX_HEIGHT;
}

void Fleaman::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case ENEMY_STATE_IDLE:
		vx = vy = 0;
		break;
	case FLEAMAN_STATE_PREATTACK:
		vx = vy = 0;
		break;
	case FLEAMAN_STATE_ATTACK:
		vy = -FLEAMAN_SPEED_Y_ATTACK;
		y -= 5;
		vx = FLEAMAN_SPEED_X;
		break;
	case ENEMY_STATE_ACTIVE:
		vy = -FLEAMAN_SPEED_Y_NORMAL;
		vx = FLEAMAN_SPEED_X;
		break;
	default:
		break;
	}
}

void Fleaman::StartActive()
{
	SetState(FLEAMAN_STATE_ATTACK);
	vy = -FLEAMAN_SPEED_Y_NORMAL;
	y -= 10;
	isActive = true;
	//ison
	isFirstJump = false;
	firstJumpStart = GetTickCount();
}

void Fleaman::Reset()
{
	this->x = firstPos.x;
	this->y = firstPos.y;

	isStartAttack = false;
	isActive = false;
	isFirstJump = true;
	firstJumpStart = jumpOnGroundStart = attackStart = onGroundStart = 0;
	score = 200;
	health = 1;

	id = ID_FLEAMAN;
	SetState(FLEAMAN_STATE_PREATTACK);
}
