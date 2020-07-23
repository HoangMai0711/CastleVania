#include "Portal.h"


CPortal::CPortal(int width, int height, D3DXVECTOR2 position, int nextSceneId, int simonNx)
{
	this->width = width;
	this->height = height;
	x = position.x;
	y = position.y;

	id = ID_PORTAL;
	scene_id = nextSceneId;
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