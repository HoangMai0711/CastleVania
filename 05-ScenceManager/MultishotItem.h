#pragma once

#include "Item.h"

#define MULTISHOT_ITEM_GRAVITY			0.0003f
#define MULTISHOT_ITEM_BBOX_WIDTH		15
#define MULTISHOT_ITEM_BBOX_HEIGHT		15

class MultishotItem :
	public Item
{
public:
	MultishotItem(D3DXVECTOR2 position, int idShotItem);
	~MultishotItem();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *nonGridObject, set<LPGAMEOBJECT> gridObject);
};

