#pragma once

#include "GameObject.h"

class TransparentObjects: public CGameObject
{
public:
	TransparentObjects();
	~TransparentObjects();

	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
};

