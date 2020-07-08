#include "MultishotItem.h"


MultishotItem::MultishotItem(D3DXVECTOR2 position, int idShotItem)
{
	this->x = position.x;
	this->y = position.y;

	this->id = idShotItem;

	AddAnimation(ID_ANI_DOUBLE_SHOT);
	AddAnimation(ID_ANI_TRIPLE_SHOT);
}

MultishotItem::~MultishotItem()
{
}

void MultishotItem::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + MULTISHOT_ITEM_BBOX_WIDTH;
	bottom = y + MULTISHOT_ITEM_BBOX_HEIGHT;
}

void MultishotItem::Update(DWORD dt, vector<LPGAMEOBJECT>* nonGridObject, set<LPGAMEOBJECT> gridObject)
{
	Item::Update(dt, nonGridObject, gridObject);

	if (!isOnGround)
		vy += MULTISHOT_ITEM_GRAVITY * dt;
}
