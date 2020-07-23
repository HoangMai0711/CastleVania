#include "ActiveBox.h"



ActiveBox::ActiveBox(D3DXVECTOR2 position)
{
	this->x = position.x;
	this->y = position.y;
	isActive = false;

	id = ID_ACTIVE_BBOX;
}


ActiveBox::~ActiveBox()
{
}

void ActiveBox::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + ACTIVE_BOX_BBOX_WIDTH;
	bottom = y + ACTIVE_BOX_BBOX_HEIGHT;
}

void ActiveBox::IsCollide()
{
	TileMap::GetInstance()->SetCamLtdMin(0, 511);
	TileMap::GetInstance()->SetCamLtdMax(0, 768);
}
