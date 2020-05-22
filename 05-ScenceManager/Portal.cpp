#include "Portal.h"


//CPortal::CPortal(float l, float t, float r, float b, int scene_id )
//{
//	this->scene_id = scene_id;
//	x = l; 
//	y = t;
//	width = r - l + 1;
//	height = b - t + 1;
//}

CPortal::CPortal(D3DXVECTOR2 position)
{
	x = position.x;
	y = position.y;

	id = ID_PORTAL;
}

void CPortal::Render()
{
	RenderBoundingBox();
}

void CPortal::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}