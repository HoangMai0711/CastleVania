#pragma once
#include "GameObject.h"

#define HIDDEN_OBJ_BBOX_WIDTH	15
#define HIDDEN_OBJ_BBOX_HEIGHT	10

class HiddenObject : public CGameObject
{
public:
	HiddenObject(D3DXVECTOR2 position);
	~HiddenObject();

	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Render();
};

