#pragma once

#include "TransparentObjects.h"

class DeadZone :
	public TransparentObjects
{
	int width;
	int height;
public:
	DeadZone(D3DXVECTOR2 position, int w, int h);
	~DeadZone();

	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};

