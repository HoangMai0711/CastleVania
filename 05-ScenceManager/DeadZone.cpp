#include "DeadZone.h"



DeadZone::DeadZone(D3DXVECTOR2 position, int w, int h)
{
	this->x = position.x;
	this->y = position.y;
	this->width = w;
	this->height = h;

	id = ID_DEADZONE;
}


DeadZone::~DeadZone()
{
}

void DeadZone::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}
