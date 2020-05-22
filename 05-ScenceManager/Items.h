#pragma once

#include "GameObject.h"

class Items : public CGameObject
{
public:
	Items();
	~Items();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
};

