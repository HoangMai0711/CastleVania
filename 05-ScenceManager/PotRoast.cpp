#include "PotRoast.h"



PotRoast::PotRoast(D3DXVECTOR2 position)
{
	this->x = position.x;
	this->y = position.y;

	id = ID_POT_ROAST;

	AddAnimation(ID_ANI_POT_ROAST);
}


PotRoast::~PotRoast()
{
}

void PotRoast::Update(DWORD dt, vector<LPGAMEOBJECT>* nonGridObject, set<LPGAMEOBJECT> gridObject)
{
	Item::Update(dt, nonGridObject, gridObject);

	if (!isOnGround)
		vy += POT_ROAST_GRAVITY * dt;
}

void PotRoast::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + POT_ROAST_BBOX_WIDTH;
	bottom = y + POT_ROAST_BBOX_HEIGHT;
}
