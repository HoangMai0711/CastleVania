#include "Ghost.h"

Ghost::Ghost(D3DXVECTOR2 position)
{
	this->x = position.x;
	this->y = position.y;
	id = ID_GHOST;
	isActive = false;

	state = ENEMY_STATE_HIDDEN;
	vx = vy = 0;
	score = 200;

	AddAnimation(ID_ANI_GHOST_FLY_RIGHT);
	AddAnimation(ID_ANI_GHOST_FLY_LEFT);

}


Ghost::~Ghost()
{
}

void Ghost::Render()
{
	int ani = 0;

	switch (state)
	{
	case ENEMY_STATE_DIE:
		ani = ENEMY_ANI_HITTED;
		break;
	case ENEMY_STATE_ACTIVE:
		if (nx > 0)
			ani = GHOST_ANI_FLY_RIGHT;
		else
			ani = GHOST_ANI_FLY_LEFT;
		break;
	case ENEMY_STATE_HIDDEN:
		ani = ENEMY_ANI_HIDDEN;
		break;
	default:
		break;
	}
	if (hitEffectStart > 0)
		ani = ENEMY_ANI_HITTED;

	animations[ani]->Render(x, y);
}

void Ghost::Update(DWORD dt, vector<LPGAMEOBJECT> *nonGridObject, set<LPGAMEOBJECT> gridObject)
{
	CGameObject::Update(dt, nonGridObject, gridObject);
	x += dx;
	y += dy;

	float sl, st, sr, sb;
	float gl, gt, gr, gb;

	Simon* simon = Simon::GetInstance();

	simon->GetBoundingBox(sl, st, sr, sb);
	GetBoundingBox(gl, gt, gr, gb);

	if (abs(gl - sl) > GHOST_ACTIVE_DISTANCE_WIDTH && abs(gt - st) < GHOST_ACTIVE_DISTANCE_HEIGHT)
		state = ENEMY_STATE_ACTIVE;
		//state = ENEMY_STATE_IDLE;
	
	if (state == ENEMY_STATE_ACTIVE) {
		isActive = true;

		if (x > simon->GetX() + SIMON_BBOX_WIDTH / 2 + GHOST_DISTANCE_TO_SIMON_WIDTH) {
			nx = -1;
			vx = -GHOST_SPEED_X;
			vy = -GHOST_SPEED_Y;
		}
		else if (x < simon->GetX() - GHOST_DISTANCE_TO_SIMON_WIDTH) {
			nx = 1;
			vx = GHOST_SPEED_X;
			vy = -GHOST_SPEED_Y;
		}

		if (y < simon->GetY() + GHOST_DISTANCE_TO_SIMON_HEIGHT)
			vy = GHOST_SPEED_Y;
		else if (y > simon->GetY())
			vy = -GHOST_SPEED_Y;
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
