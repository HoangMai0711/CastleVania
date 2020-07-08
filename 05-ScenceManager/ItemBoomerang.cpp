#include "ItemBoomerang.h"


ItemBoomerang::ItemBoomerang(D3DXVECTOR2 postion)
{
	this->x = postion.x;
	this->y = postion.y;

	id = ID_ITEM_BOOMERANG;

	AddAnimation(ID_ANI_ITEM_BOOMERANG);
}

ItemBoomerang::~ItemBoomerang()
{
}

void ItemBoomerang::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + ITEM_BOOMERANG_BBOX_WIDTH;
	bottom = y + ITEM_BOOMERANG_BBOX_HEIGHT;
}

void ItemBoomerang::Update(DWORD dt, vector<LPGAMEOBJECT> *nonGridObject, set<LPGAMEOBJECT> gridObject)
{
	Items::Update(dt, nonGridObject, gridObject);

	if (!isOnGround)
		vy += ITEM_BOOMERANG_GRAVITY * dt;
}
