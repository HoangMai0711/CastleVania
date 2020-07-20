#include "Zombie.h"


Zombie::Zombie(D3DXVECTOR2 position, int nx, int reward)
{
	DebugOut(L"----Zombie appear\n");
	this->x = position.x;
	this->y = position.y;
	this->nx = nx;
	this->idReward = reward;

	//vx = nx * ZOMBIE_SPEED_X;
	state = ENEMY_STATE_ACTIVE;

	id = ID_ZOMBIE;

	AddAnimation(ID_ANI_ZOMBIE_WALK_RIGHT);
	AddAnimation(ID_ANI_ZOMBIE_WALK_LEFT);
}

Zombie::~Zombie()
{
}

void Zombie::Render()
{
	int ani = 0;
	switch (state)
	{
	case ENEMY_STATE_DIE:
		ani = ENEMY_ANI_HITTED;
		break;
	case ENEMY_STATE_ACTIVE:
		if (nx > 0)
			ani = ZOMBIE_ANI_WALK_RIGHT;
		else
			ani = ZOMBIE_ANI_WALK_LEFT;
		break;
	default:
		break;
	}
	animations[ani]->Render(x, y);
}

void Zombie::Update(DWORD dt, vector<LPGAMEOBJECT> *nonGridObject, set<LPGAMEOBJECT> gridObject)
{
	Enemy::Update(dt, nonGridObject, gridObject);

	x += dx;
	vx = nx * ZOMBIE_SPEED_X;

	if (state != ENEMY_STATE_DIE)
		vy += ZOMBIE_GRAVITY * dt;
}

void Zombie::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (state == ENEMY_STATE_ACTIVE) {
		left = x;
		top = y;
		right = x + ZOMBIE_BBOX_WIDTH;
		bottom = y + ZOMBIE_BBOX_HEIGHT;
	}
	else
		left = top = right = bottom = 0;
}
