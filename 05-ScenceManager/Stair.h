#pragma once

#include "TransparentObjects.h"

class Stair :public TransparentObjects
{
	int height;
	int bboxWidth;
	int bboxHeight;
public:
	Stair(D3DXVECTOR2 position, int height, int bbw, int bbh, int nx, int ny);
	~Stair();

	int GetStairHeight() { return height; }
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

