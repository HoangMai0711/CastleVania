#pragma once

#include "GroundObject.h"

class TransparentObjects: public GroundObject
{
public:
	TransparentObjects();
	~TransparentObjects();

	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *nonGridObject, set<LPGAMEOBJECT> gridObject);
};

