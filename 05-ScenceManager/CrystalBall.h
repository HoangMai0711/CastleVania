#pragma once

#include "Item.h"

#define CRYSTAL_BALL_BBOX_WIDTH			15
#define CRYSTAL_BALL_BBOX_HEIGHT		15

#define CRYSTAL_BALL_GRAVITY		0.0002f

class CrystalBall :
	public Item
{
public:
	CrystalBall(D3DXVECTOR2 position);
	~CrystalBall();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *nonGridObject, set<LPGAMEOBJECT> gridObject);
};

