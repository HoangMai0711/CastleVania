#pragma once

#include "Items.h"

#define MONEYBAG_BBOX_WIDTH			15
#define MONEYBAG_BBOX_HEIGHT		15
#define MONEYBAG_GRAVITY			0.0004f

class MoneyBag : public Items
{
	DWORD showtime;
public:
	MoneyBag(D3DXVECTOR2 position);
	~MoneyBag();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *objects);
	virtual void Render();
};

