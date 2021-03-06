#pragma once
#include "Item.h"

#define BIG_HEART_BBOX_WIDTH		13
#define BIG_HEART_BBOX_HEIGHT		11
#define BIG_HEART_GRAVITY			0.0007f

class BigHeart : public Item
{
public:
	BigHeart(D3DXVECTOR2 position);
	~BigHeart();

	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *nonGridObject, set<LPGAMEOBJECT> gridObject);
};

