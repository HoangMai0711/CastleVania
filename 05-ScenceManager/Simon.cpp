#include "Simon.h"


Simon* Simon::__instance;

Simon::Simon()
{
	DebugOut(L"[INFO]Create Simon and add animation\n");

	AddAnimation(ID_ANI_SIMON_IDLE_RIGHT);				// Idle Right			0
	AddAnimation(ID_ANI_SIMON_IDLE_LEFT);				// Idle Left			1
	AddAnimation(ID_ANI_SIMON_WALK_RIGHT);				// Walk Right			2
	AddAnimation(ID_ANI_SIMON_WALK_LEFT);				// Walk Left			3
	AddAnimation(ID_ANI_SIMON_ATTACK_RIGHT);			// Attack Right			4
	AddAnimation(ID_ANI_SIMON_ATTACK_LEFT);				// Attack Left			5
	AddAnimation(ID_ANI_SIMON_SIT_RIGHT);				// Sit Right			6
	AddAnimation(ID_ANI_SIMON_SIT_LEFT);				// Sit Left				7
	AddAnimation(ID_ANI_SIMON_SIT_ATTACK_RIGHT);		// Sit Attack Right		8
	AddAnimation(ID_ANI_SIMON_SIT_ATTACK_LEFT);			// Sit Attack Left		9
	AddAnimation(ID_ANI_SIMON_DIE);						// Die					10
	AddAnimation(ID_ANI_SIMON_IDLE_UPSTAIR_RIGHT);		// Idle Upstair Right		11
	AddAnimation(ID_ANI_SIMON_IDLE_UPSTAIR_LEFT);		// Idle Upstair Left		12
	AddAnimation(ID_ANI_SIMON_IDLE_DOWNSTAIR_RIGHT);	// Idle Downstair Right		13 
	AddAnimation(ID_ANI_SIMON_IDLE_DOWNSTAIR_LEFT);		// Idle Downstair Left		14
	AddAnimation(ID_ANI_SIMON_WALK_UPSTAIR_RIGHT);		// Walk Upstair Right		15
	AddAnimation(ID_ANI_SIMON_WALK_UPSTAIR_LEFT);		// Walk Upstair Left		16
	AddAnimation(ID_ANI_SIMON_WALK_DOWNSTAIR_RIGHT);	// Walk Downstair Right		17
	AddAnimation(ID_ANI_SIMON_WALK_DOWNSTAIR_LEFT);		// Walk Downstair Left		18
	AddAnimation(ID_ANI_SIMON_ATTACK_UPSTAIR_RIGHT);	// Attack Upstair Right		19
	AddAnimation(ID_ANI_SIMON_ATTACK_UPSTAIR_LEFT);		// Attack Upstair Left		20
	AddAnimation(ID_ANI_SIMON_ATTACK_DOWNSTAIR_RIGHT);	// Attack Downstair Right	21
	AddAnimation(ID_ANI_SIMON_ATTACK_DOWNSTAIR_LEFT);	// Attack Downstair Left	22
	AddAnimation(ID_ANI_SIMON_INJURED_DEFLECT_RIGHT);	// Injured Deflect Right	23
	AddAnimation(ID_ANI_SIMON_INJURED_DEFLECT_LEFT);	// Injured Deflect Left		24
	AddAnimation(ID_ANI_SIMON_FLASH_RIGHT);				// Flash Right				25
	AddAnimation(ID_ANI_SIMON_FLASH_LEFT);				// Flash Left				26

	id = ID_SIMON;
	isOnAir = false;
	attackStart = 0;

	whip = new Whip();
}


Simon::~Simon()
{
	delete __instance;
	__instance = NULL;
}

Simon * Simon::GetInstance()
{
	if (__instance == NULL) __instance = new Simon();
	return __instance;
}

void Simon::Jump()
{
	SetState(SIMON_STATE_JUMP);
	isOnAir = true;
}

void Simon::StartAttack()
{
	if (attackStart > 0)
		return;
	ResetAnimation();

	if (state == SIMON_STATE_SIT)
		SetState(SIMON_STATE_SIT_ATTACK);
	else
		SetState(SIMON_STATE_ATTACK);

	attackStart = GetTickCount();
}

void Simon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (GetTickCount() - attackStart > 300)
		attackStart = 0;

	UpdateWhip(dt, coObjects);

	CGameObject::Update(dt);

	vy += SIMON_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	//// turn off collision when die 
	//if (state != SIMON_STATE_DIE)
	CalcPotentialCollisions(coObjects, coEvents);

	//vector<LPGAMEOBJECT> wallObjects;

	//for (UINT i = 0; i < coEventsResult.size(); i++)
	//{
	//	LPCOLLISIONEVENT e = coEventsResult[i];
	//	if (dynamic_cast<Wall*>(e->obj)) {
	//		wallObjects.push_back(coObjects->at(i));
	//	}
	//}

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// block 
		isOnAir = false;

		if (state == SIMON_STATE_ATTACK)
			SetSpeed(0, 0);

		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0)
			vx = 0;
		if (ny != 0)
			vy = 0;

		// Collision logic with Goombas
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			//if (dynamic_cast<CGoomba *>(e->obj)) // if e->obj is Goomba 
			//{
			//	CGoomba *goomba = dynamic_cast<CGoomba *>(e->obj);
			//	// jump on top >> kill Goomba and deflect a bit 
			//	if (e->ny < 0)
			//	{
			//		if (goomba->GetState() != GOOMBA_STATE_DIE)
			//		{
			//			goomba->SetState(GOOMBA_STATE_DIE);
			//			vy = -MARIO_JUMP_DEFLECT_SPEED;
			//		}
			//	}
			//	else if (e->nx != 0)
			//	{
			//		if (untouchable == 0)
			//		{
			//			if (goomba->GetState() != GOOMBA_STATE_DIE)
			//			{
			//				SetState(SIMON_STATE_FLASH);
			//				StartUntouchable();
			//			}
			//			else
			//				SetState(SIMON_STATE_DIE);
			//		}
			//	}
			//}

			//Collion with Torch
			if (dynamic_cast<Torch*>(e->obj))
			{
				DebugOut(L"[INFO] Collision Simon and Torch %d %d\n", e->nx, e->ny);
				// Process normally
				if (e->nx != 0) x += dx;
				if (e->ny != 0) y += dy;
			}

		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	if (state == SIMON_STATE_ATTACK || state == SIMON_STATE_SIT_ATTACK)
	{
		DebugOut(L"-------simon attacking\n");
		for (auto i : animations) {
			// Only check collsion at the last frame of the whip
			if (i->GetCurrentFrame() == 2) 
			{
				for (UINT i = 0; i < coObjects->size(); i++)
				{
					LPGAMEOBJECT collideObject = coObjects->at(i);
					if (dynamic_cast<Torch*>(collideObject))
					{
						DebugOut(L">>>>Collide\n");
						Torch* torch = dynamic_cast<Torch*> (collideObject);
						float firstLeft, firstTop, firstRight, firstBottom;
						float secLeft, secTop, secRight, secBottom;
						torch->GetBoundingBox(firstLeft, firstTop, firstRight, firstBottom);
						whip->GetBoundingBox(secLeft, secTop, secRight, secBottom);

						if (CGame::GetInstance()->IsColliding({ long(firstLeft),long(firstTop),long(firstRight),long(firstBottom) }, { long(secLeft),long(secTop),long(secRight),long(secBottom) })) {
							DebugOut(L"[INFO]Whip collide with Torch\n");
							torch->SetState(STATIC_OBJ_STATE_HITTED);
						}
					}
				}
			}
		}
	}
}

void Simon::Render()
{
	int ani = -1;

	switch (state)
	{
	case SIMON_STATE_DIE:
		ani = SIMON_ANI_DIE;
		break;
	case SIMON_STATE_ATTACK:
		if (nx > 0)
			ani = SIMON_ANI_ATTACK_RIGHT;
		else
			ani = SIMON_ANI_ATTACK_LEFT;
		break;
	case SIMON_STATE_SIT_ATTACK:
		if (nx > 0)
			ani = SIMON_ANI_SIT_ATTACK_RIGHT;
		else
			ani = SIMON_ANI_SIT_ATTACK_LEFT;
		break;
	case SIMON_STATE_JUMP:
		if (nx > 0)
			ani = SIMON_ANI_IDLE_RIGHT;
		else
			ani = SIMON_ANI_IDLE_LEFT;
	case SIMON_STATE_SIT:
		if (nx > 0)
			ani = SIMON_ANI_SIT_RIGHT;
		else
			ani = SIMON_ANI_SIT_LEFT;
		break;
	case SIMON_STATE_UPSTAIR:
		if (nx > 0)
			ani = SIMON_ANI_WALK_UPSTAIR_RIGHT;
		else
			ani = SIMON_ANI_WALK_UPSTAIR_LEFT;
		break;
	case SIMON_STATE_DOWNSTAIR:
		if (nx > 0)
			ani = SIMON_ANI_WALK_DOWNSTAIR_RIGHT;
		else
			ani = SIMON_ANI_WALK_DOWNSTAIR_LEFT;
		break;
	case SIMON_STATE_WALKING_RIGHT:
		ani = SIMON_ANI_WALK_RIGHT;
		break;
	case SIMON_STATE_WALKING_LEFT:
		ani = SIMON_ANI_WALK_LEFT;
		break;
	case SIMON_STATE_INJURED:
		if (nx > 0)
			ani = SIMON_ANI_INJURED_RIGHT;
		else
			ani = SIMON_ANI_INJURED_LEFT;
		break;
	case SIMON_STATE_FLASH:
		if (nx > 0)
			ani = SIMON_ANI_FLASH_RIGHT;
		else
			ani = SIMON_ANI_FLASH_LEFT;
		break;
	case SIMON_STATE_IDLE:
		if (nx > 0)
			ani = SIMON_ANI_IDLE_RIGHT;
		else
			ani = SIMON_ANI_IDLE_LEFT;
		break;
	}

	int alpha = 255;
	if (untouchable)
		alpha = 50;

	//Render animation
	//animation_set->at(ani)->Render(x, y, alpha);
	animations[ani]->Render(x, y, alpha);

	if (attackStart)
		whip->Render();

	RenderBoundingBox();
}

void Simon::SetState(int state)
{
	if (isOnAir == true)
		return;
	if (attackStart > 0)
		return;

	CGameObject::SetState(state);
	switch (state)
	{
	case SIMON_STATE_WALKING_RIGHT:
		vx = SIMON_WALKING_SPEED;
		nx = 1;
		break;
	case SIMON_STATE_WALKING_LEFT:
		vx = -SIMON_WALKING_SPEED;
		nx = -1;
		break;
	case SIMON_STATE_JUMP:
		vy = -SIMON_JUMP_SPEED_Y;
		y -= 5;
		break;
	case SIMON_STATE_IDLE:
		vx = 0;
		break;
	case SIMON_STATE_DIE:
		vx = -SIMON_DIE_DEFLECT_SPEED;
		break;
	case SIMON_STATE_ATTACK:
		break;
	case SIMON_STATE_ATTACK_ON_STAIR:
	case SIMON_STATE_SIT:
		SetSpeed(0, 0);
		break;
	case SIMON_STATE_INJURED:
		break;
	}
}

void Simon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	switch (state)
	{
	case SIMON_STATE_SIT:
	case SIMON_STATE_SIT_ATTACK:
		left = x;
		top = y + SIMON_BBOX_HEIGHT - SIMON_BBOX_SIT_HEIGHT;
		right = x + SIMON_BBOX_SIT_WIDTH;
		bottom = y + SIMON_BBOX_HEIGHT;
		break;
	default:
		left = x;
		top = y;
		right = x + SIMON_BBOX_WIDTH;
		bottom = y + SIMON_BBOX_HEIGHT;
		break;
	}
}

void Simon::UpdateWhip(DWORD dt, vector<LPGAMEOBJECT>* objects)
{
	if (GetTickCount() - attackStart <= 300)
	{
		float playerX, playerY;
		playerY = (state == SIMON_STATE_SIT_ATTACK ? y + SIMON_BBOX_HEIGHT / 4 : y);
		playerX = x - 2 * nx;

		whip->Update(dt, objects, { playerX, playerY }, nx);
	}
	else if (attackStart > 0)
	{
		attackStart = 0;
		state = (state == SIMON_STATE_SIT_ATTACK ? SIMON_STATE_SIT : SIMON_STATE_IDLE);
		whip->ResetAnimation();
	}
}

void Simon::UpgradeWhip()
{
	whip->Upgrade();
}
