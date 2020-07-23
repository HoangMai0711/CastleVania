#pragma once

#include "TransparentObjects.h"

#define ONE_WAY_WALL_BBOX_WIDTH		11
#define ONE_WAY_WALL_BBOX_HEIGHT	178

class OneWayWall :
	public TransparentObjects
{
public:
	OneWayWall(D3DXVECTOR2 position);
	~OneWayWall();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

