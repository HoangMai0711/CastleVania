#pragma once
#include "Items.h"

#define WHIP_UPGRADE_BBOX_WIDTH			18
#define WHIP_UPGRADE_BBOX_HEIGHT		18
#define WHIP_UPGRADE_GRAVITY			0.0005f

class WhipUpgrade : public Items
{
public:
	WhipUpgrade(D3DXVECTOR2 postition);
	~WhipUpgrade();

	void GetBoundingBox(float& left, float &top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};

