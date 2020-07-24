#include "Bat.h"


Bat::Bat(D3DXVECTOR2 position, int reward)
{
	this->x = position.x;
	this->y = position.y;
	this->idReward = reward;

	this->firstPos = position;

	delta = 0;
	originY = y;
	startFlyDown = 0;
	isActive = false;
	health = 1;
	score = 200;

	SetState(ENEMY_STATE_IDLE);

	id = ID_BAT;

	AddAnimation(ID_ANI_BAT_IDLE);
	AddAnimation(ID_ANI_BAT_FLY);
}

Bat::~Bat()
{
}

void Bat::Render()
{
	int ani;

	switch (state)
	{
	case ENEMY_STATE_IDLE:
		ani = BAT_ANI_IDLE;
		break;
	case BAT_FLY_DOWN:
	case BAT_FLY_NORMAL:
		ani = BAT_ANI_FLY;
		break;
	case ENEMY_STATE_DIE:
		DebugOut(L"----Render ani hitted\n");
		ani = ENEMY_ANI_HITTED;
		break;
	default:
		break;
	}
	if (hitEffectStart > 0)
		ani = ENEMY_ANI_HITTED;
	animations[ani]->Render(x, y);
}

void Bat::Update(DWORD dt, vector<LPGAMEOBJECT> *nonGridObject, set<LPGAMEOBJECT> gridObject)
{
	CGameObject::Update(dt, nonGridObject, gridObject);
	x += dx;
	y += dy;
	if (state == ENEMY_STATE_IDLE) {
		float sl, st, sr, sb;
		float bl, bt, br, bb;

		Simon::GetInstance()->GetBoundingBox(sl, st, sr, sb);
		GetBoundingBox(bl, bt, br, bb);

		//DebugOut(L"------Bl-Sl-Bb-St: %f/ %f/ %f/ %f\n", bl, sl, bb, st);
		//Check if bat is active

		if (abs(bl - sl) < BAT_ACTIVE_DISTANCE_WIDTH && abs(bb - st) < BAT_ACTIVE_DISTANCE_HEIGHT) {
			if (!isActive)
			{
				isActive = true;
				startFlyDown = GetTickCount();
				SetState(BAT_FLY_DOWN);
			}

		}
	}

	//Bat fly down
	if (startFlyDown > 0 && GetTickCount() - startFlyDown >= BAT_TIME_FLYDOWN) {
		startFlyDown = 0;
		originY = y;
	}

	//Fly normal
	if (startFlyDown == 0 && isActive) {
		x += dx;
		SetState(BAT_FLY_NORMAL);
	}

	DWORD effectTimeCount = GetTickCount() - hitEffectStart;
	if (effectTimeCount > HIT_EFFECT_TIME && hitEffectStart > 0) {
		hitEffectStart = 0;
		state = STATE_DESTROYED;

		LPGAMEOBJECT reward;
		int rewardId = GetRewardId();

		switch (rewardId)
		{
		case ID_BIG_HEART:
			reward = new BigHeart({ x,y });
			break;
		case ID_WHIP_UPGRADE:
			reward = new WhipUpgrade({ x,y });
			break;
		case ID_DAGGER:
			reward = new ItemDagger({ x,y });
			break;
		case ID_ITEM_BOOMERANG:
			reward = new ItemBoomerang({ x,y });
			break;
		case ID_SMALL_HEART:
			reward = new SmallHeart({ x,y });
			break;
		default:
			reward = NULL;
			break;
		}
		if (reward)
			nonGridObject->push_back(reward);
	}

	if (state == ENEMY_STATE_IDLE)
		return;
	else {

		//Delete when bat fly out of screen
		float al, at, ar, ab;
		float bl, bt, br, bb;

		float x = CGame::GetInstance()->GetCamPosX();
		float y = CGame::GetInstance()->GetCamPosY();

		al = x;
		at = y;
		ar = x + SCREEN_WIDTH;
		ab = y + SCREEN_HEIGHT;

		GetBoundingBox(bl, bt, br, bb);

		RECT A, B;
		A = { long(al),long(at),long(ar),long(ab) };
		B = { long(bl),long(bt),long(br),long(bb) };

		if (!CGame::GetInstance()->IsColliding(A, B)) {
			//DebugOut(L"-----Bat vx, vy, state: %f/ %f/ %d\n", vx, vy, state);
			//DebugOut(L"------Bat fly out off screen\n");
			state = STATE_DESTROYED;
		}
	}
}

void Bat::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (state != ENEMY_STATE_DIE) {
		left = x;
		top = y;
		right = x + BAT_BBOX_WIDTH;
		bottom = y + BAT_BBOX_HEIGHT;
	}
	else
		left = top = right = bottom = 0;
}

void Bat::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BAT_FLY_DOWN:
		vx = BAT_SPEED_X;
		vy = BAT_SPEED_y;
		break;
	case ENEMY_STATE_IDLE:
		vx = vy = 0;
		break;
	case BAT_FLY_NORMAL:
		delta += 3.7f;
		y = sin(delta * 3.14 / 180) * 12 + originY;
		break;
	}
}

void Bat::Reset()
{
	this->x = firstPos.x;
	this->y = firstPos.y;

	delta = 0;
	originY = y;
	startFlyDown = 0;
	isActive = false;
	health = 1;
	score = 200;

	SetState(ENEMY_STATE_IDLE);

	id = ID_BAT;
}
