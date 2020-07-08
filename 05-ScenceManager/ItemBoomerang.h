#pragma once

#include "Items.h"

#define ITEM_BOOMERANG_BBOX_WIDTH		14
#define ITEM_BOOMERANG_BBOX_HEIGHT		14

#define ITEM_BOOMERANG_GRAVITY			0.0005f

class ItemBoomerang : public Items
{
public:
	ItemBoomerang(D3DXVECTOR2 postion);
	~ItemBoomerang();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *nonGridObject, set<LPGAMEOBJECT> gridObject);
};

