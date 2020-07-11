#pragma once

#include "Item.h"

#define POT_ROAST_BBOX_WIDTH		18
#define POT_ROAST_BBOX_HEIGHT		15

#define POT_ROAST_GRAVITY		0.0004f

class PotRoast :
	public Item
{
public:
	PotRoast(D3DXVECTOR2 position);
	~PotRoast();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *nonGridObject, set<LPGAMEOBJECT> gridObject);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

