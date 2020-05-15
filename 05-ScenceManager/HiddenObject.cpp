#include "HiddenObject.h"

HiddenObject::HiddenObject(D3DXVECTOR2 position)
{
	x = position.x;
	y = position.y;
}

HiddenObject::~HiddenObject()
{
}

void HiddenObject::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + HIDDEN_OBJ_BBOX_WIDTH;
	b = y + HIDDEN_OBJ_BBOX_HEIGHT;
}

void HiddenObject::Render()
{
	RenderBoundingBox();
}
