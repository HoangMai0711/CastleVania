#pragma once

#include "StaticObjects.h"

#define TORCH_BBOX_WIDTH		18
#define TORCH_BBOX_HEIGHT		30

class Torch : public StaticObjects
{
public:
	Torch(D3DXVECTOR2 position, int reward);
	~Torch();

	virtual void GetBoundingBox(float &l, float &r, float &t, float &b);
};

