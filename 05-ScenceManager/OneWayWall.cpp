#include "OneWayWall.h"



OneWayWall::OneWayWall(D3DXVECTOR2 position)
{
	this->x = position.x;
	this->y = position.y;

	id = ID_ONE_WAY_WALL;
}


OneWayWall::~OneWayWall()
{
}

void OneWayWall::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + ONE_WAY_WALL_BBOX_WIDTH;
	bottom = y + ONE_WAY_WALL_BBOX_HEIGHT;
}
