#pragma once
#include "GroundObject.h"
#include "MoneyBag.h"

#define HIDDEN_OBJ_BBOX_WIDTH	15
#define HIDDEN_OBJ_BBOX_HEIGHT	10

class HiddenObject : public GroundObject
{
	D3DXVECTOR2 rewardPosition;
	int width;
	int height;
public:
	HiddenObject(D3DXVECTOR2 position, int reward, D3DXVECTOR2 rewardPos, int width, int height);
	~HiddenObject();

	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Render();
	virtual void IsCollide(vector<LPGAMEOBJECT>* objects);
};

