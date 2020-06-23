#include "Fleaman.h"

Fleaman::Fleaman(D3DXVECTOR2 position)
{
	this->x = position.x;
	this->y = position.y;
	
	id = ID_FLEAMAN;
	state = FLEAMAN_STATE_PREATTACK;

	AddAnimation(ID_ANI_FLEAMAN_IDLE_RIGHT);
	AddAnimation(ID_ANI_FLEAMAN_IDLE_LEFT);
	AddAnimation(ID_ANI_FLEAMAN_PREATTACK);
}


Fleaman::~Fleaman()
{
}

void Fleaman::Render()
{
	int ani = 0;

	switch (state)
	{
	case FLEAMAN_STATE_PREATTACK:
		ani = FLEAMAN_ANI_PREATTACK;
		break;
	case ENEMY_STATE_IDLE:
		if (nx > 0)
			ani = FLEAMAN_ANI_IDLE_RIGHT;
		else
			ani = FLEAMAN_ANI_IDLE_LEFT;
		break;
	default:
		break;
	}
	animations[ani]->Render(x, y);
}

void Fleaman::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{
	Enemy::Update(dt, objects);
}

void Fleaman::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (state != ENEMY_ANI_HITTED) {
		left = x;
		top = y;
		right = x + FLEAMAN_BBOX_WIDTH;
		bottom = y + FLEAMAN_BBOX_HEIGHT;
	}
	else
		left = top = right = bottom = 0;
}
