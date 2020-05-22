#pragma once
#include "Items.h"

#define ITEM_DAGGER_BBOX_WIDTH		18
#define ITEM_DAGGER_BBOX_HEIGHT		10
#define ITEM_DAGGER_GRAVITY			0.0005f

class ItemDagger : public Items
{
public:
	ItemDagger(D3DXVECTOR2 position);
	~ItemDagger();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};

