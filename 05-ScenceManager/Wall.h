#pragma once

#include "TransparentObjects.h"

class Wall : public TransparentObjects
{
	int width;
	int height;
public:
	Wall();
	Wall(D3DXVECTOR2 position, int width, int height);
	~Wall();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

