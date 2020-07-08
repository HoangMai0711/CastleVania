#include "ItemDagger.h"


ItemDagger::ItemDagger(D3DXVECTOR2 position)
{
	this->x = position.x;
	this->y = position.y;
	id = ID_DAGGER;

	AddAnimation(ID_ANI_DAGGER_LEFT);
}

ItemDagger::~ItemDagger()
{
}

void ItemDagger::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + ITEM_DAGGER_BBOX_WIDTH;
	bottom = y + ITEM_DAGGER_BBOX_HEIGHT;
}

void ItemDagger::Update(DWORD dt, vector<LPGAMEOBJECT> *nonGridObject, set<LPGAMEOBJECT> gridObject)
{
	Item::Update(dt, nonGridObject, gridObject);

	if (!isOnGround)
		vy += ITEM_DAGGER_GRAVITY * dt;
}
