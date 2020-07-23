#pragma once
#include "StaticObjects.h"
#include "BreakableBrickEffect.h"

#define BRICK_BBOX_WIDTH  16
#define BRICK_BBOX_HEIGHT 13

class CBrick : public StaticObjects
{
	bool isBroken;
public:
	CBrick(D3DXVECTOR2 position, int reward, int idAni);
	~CBrick();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *nonGridObject, set<LPGAMEOBJECT> gridObject);
	virtual void Render();
	virtual void IsHitted(vector<LPGAMEOBJECT> *nonGridObject = NULL);
};