#include "Whip.h"



int Whip::GetCurrentAnimation()
{
	int ani = 0;
	if (level == 0 && nx > 0)
		ani = 0;
	else if (level == 0 && nx < 0)
		ani = 1;
	else if (level == 1 && nx > 0)
		ani = 2;
	else if (level == 1 && nx < 0)
		ani = 3;
	else if (level == 2 && nx > 0)
		ani = 4;
	else
		ani = 5;

	return ani;
}

Whip::Whip()
{
	id = ID_WHIP;
	vx = 0;
	vy = 0;
	level = 0;

	AddAnimation(ID_ANI_WHIP_SHORT_RIGHT);			// Level 1 Right - Ani ID: 0
	AddAnimation(ID_ANI_WHIP_SHORT_LEFT);			// Level 1 Left - Ani ID: 1
	AddAnimation(ID_ANI_WHIP_NORMAL_RIGHT);			// Level 2 Right - Ani ID: 2
	AddAnimation(ID_ANI_WHIP_NORMAL_LEFT);			// Level 2 Left - Ani ID: 3
	AddAnimation(ID_ANI_WHIP_LONG_RIGHT);			// Level 3 Right - Ani ID: 4
	AddAnimation(ID_ANI_WHIP_LONG_LEFT);			// Level 3 Left - Ani ID: 5
}


Whip::~Whip()
{
}

void Whip::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, D3DXVECTOR2 playerPos, int playerNx)
{
	this->x = playerPos.x;
	this->y = playerPos.y;
	this->nx = playerNx;
}

void Whip::GetBoundingBox(float & left, float & top, float &right, float & bottom)
{

}

void Whip::Render()
{
	animations[GetCurrentAnimation()]->Render(x, y);
}

void Whip::Upgrade()
{
	if (level < 2)
		level++;
}
