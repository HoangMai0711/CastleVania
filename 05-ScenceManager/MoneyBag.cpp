#include "MoneyBag.h"


MoneyBag::MoneyBag(D3DXVECTOR2 position)
{
	this->x = position.x;
	this->y = position.y;

	id = ID_BIG_MONEYBAG;
	AddAnimation(ID_ANI_BIG_MONEYBAG);
	showtime = GetTickCount();
}

MoneyBag::~MoneyBag()
{
}

void MoneyBag::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + MONEYBAG_BBOX_WIDTH;
	bottom = y + MONEYBAG_BBOX_HEIGHT;
}

void MoneyBag::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{
	Items::Update(dt, objects);

	if (!isOnGround)
		vy += MONEYBAG_GRAVITY * dt;
}

void MoneyBag::Render()
{
	animations[0]->Render(x, y);
}
