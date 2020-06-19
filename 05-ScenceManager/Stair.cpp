#include "Stair.h"


Stair::Stair(D3DXVECTOR2 position, int height, int bbw, int bbh, int nx, int ny)
{
	this->x = position.x;
	this->y = position.y;
	this->height = height;
	this->bboxWidth = bbw;
	this->bboxHeight = bbh;
	this->nx = nx;
	this->ny = ny;

	id = ID_STAIR;
	//DebugOut(L"---Stair nx: %d\n", nx);
}

Stair::~Stair()
{
}

void Stair::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + bboxWidth;
	bottom = top + bboxHeight;
}
