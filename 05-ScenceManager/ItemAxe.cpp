#include "ItemAxe.h"



ItemAxe::ItemAxe(D3DXVECTOR2 position)
{
	this->x = position.x;
	this->y = position.y;

	id = ID_ITEM_AXE;
	AddAnimation(ID_ANI_ITEM_AXE);
}

ItemAxe::~ItemAxe()
{
}

void ItemAxe::Update(DWORD dt, vector<LPGAMEOBJECT> *nonGridObject, set<LPGAMEOBJECT> gridObject)
{
	Items::Update(dt, nonGridObject, gridObject);

	if (!isOnGround)
		vy += ITEM_AXE_GRAVITTY * dt;
}

void ItemAxe::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + ITEM_AXE_BBOX_WIDTH;
	bottom = y + ITEM_AXE_BBOX_HEIGHT;
}
