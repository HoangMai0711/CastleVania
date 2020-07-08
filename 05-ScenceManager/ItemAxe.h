#pragma once
#include "Item.h"

#define ITEM_AXE_BBOX_WIDTH		15
#define ITEM_AXE_BBOX_HEIGHT	15

#define ITEM_AXE_GRAVITTY		0.0005f

class ItemAxe :
	public Item
{
public:
	ItemAxe(D3DXVECTOR2 position);
	~ItemAxe();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *nonGridObject, set<LPGAMEOBJECT> gridObject);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

