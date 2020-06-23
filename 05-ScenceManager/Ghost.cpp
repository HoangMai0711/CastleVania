#include "Ghost.h"


Ghost::Ghost(D3DXVECTOR2 position)
{
	this->x = position.x;
	this->y = position.y;
	id = ID_GHOST;
	isActive = false;

	state = GHOST_STATE_HIDDEN;
	vx = vy = 0;

	AddAnimation(ID_ANI_GHOST_FLY_RIGHT);
	AddAnimation(ID_ANI_GHOST_FLY_LEFT);

	AddAnimation(ID_ANI_GHOST_HIDDEN);
}


Ghost::~Ghost()
{
}

void Ghost::Render()
{
	int ani = 0;

	switch (state)
	{
	case GHOST_STATE_HIDDEN:
		ani = GHOST_ANI_HIDDEN;
		break;
	case ENEMY_STATE_HITTED:
		ani = ENEMY_ANI_HITTED;
		break;
	case ENEMY_STATE_ACTIVE:
		if (nx > 0)
			ani = GHOST_ANI_FLY_RIGHT;
		else
			ani = GHOST_ANI_FLY_LEFT;
		break;
	default:
		break;
	}

	animations[ani]->Render(x, y);
}

void Ghost::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{
	CGameObject::Update(dt);
	x += dx;
	y += dy;

	float sl, st, sr, sb;
	float gl, gt, gr, gb;

	Simon* simon = Simon::GetInstance();

	simon->GetBoundingBox(sl, st, sr, sb);
	GetBoundingBox(gl, gt, gr, gb);

	if (abs(gl - sl) > 100 && abs(gt - st) < 30) {
		x += dx;
		y += dy;
		//DebugOut(L"-----Ghost is active. NX: %d\n", nx);
		state = ENEMY_STATE_ACTIVE;
	}
	if (state == ENEMY_STATE_ACTIVE) {
		isActive = true;

		if (!isActive && x < simon->GetX() - GHOST_DISTANCE_TO_SIMON)
		{
			nx = 1;
			isActive = true;
		}

		if (isActive)
		{
			if (x > simon->GetX() + SIMON_BBOX_WIDTH / 2 + GHOST_DISTANCE_TO_SIMON)
			{
				nx = -1;
				vx = -GHOST_SPEED_X;
				vy = -GHOST_SPEED_Y;

			}
			else if (x < simon->GetX() - GHOST_DISTANCE_TO_SIMON)
			{
				nx = 1;
				vx = GHOST_SPEED_X;
				vy = -GHOST_SPEED_Y;
			}
		}

		if (y < simon->GetY() + 5)
		{
			vy = GHOST_SPEED_Y;
		}
		else if (y > simon->GetY())
		{
			vy = -GHOST_SPEED_Y;
		}
	}
	DWORD effectTimeCount = GetTickCount() - hitEffectStart;
	if (effectTimeCount > HIT_EFFECT_TIME && hitEffectStart > 0) {
		hitEffectStart = 0;

		state = STATE_DESTROYED;
	}
}

void Ghost::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{

		left = x;
		top = y;
		right = x + GHOST_BBOX_WIDTH;
		bottom = y + GHOST_BBOX_HEIGHT;

}
