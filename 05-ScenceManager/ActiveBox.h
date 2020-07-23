#pragma once

#include "TransparentObjects.h"
#include "TileMap.h"

#define ACTIVE_BOX_BBOX_WIDTH		4
#define ACTIVE_BOX_BBOX_HEIGHT		17

class ActiveBox :
	public TransparentObjects
{
	bool isActive;
public:
	ActiveBox(D3DXVECTOR2 position);
	~ActiveBox();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void IsCollide();

	bool IsActive() { return isActive; }
};

