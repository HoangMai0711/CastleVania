#include "Wall.h"



Wall::Wall()
{
	width = 16;
	height = 16;
	x = 0;
	y = 0;

	id = ID_WALL;
}

Wall::Wall(D3DXVECTOR2 position, int width, int height)
{
	this->width = width;
	this->height = height;
	this->x = position.x;
	this->y = position.y;

	id = ID_WALL;
}


Wall::~Wall()
{
}

void Wall::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
	//DebugOut(L"[INFO]Wall BBOX: : %f-%f-%f-%f\n", left, top, right, bottom);
}
