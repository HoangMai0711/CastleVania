#include "Boomerang.h"


Boomerang::Boomerang(D3DXVECTOR2 position, int nx)
{
	this->x = position.x;
	this->y = position.y;
	this->nx = nx;

	id = ID_BOOMERANG;
	vx = nx * BOOMERANG_SPEED;

	AddAnimation(ID_ANI_BOOMERANG_RIGHT);
	AddAnimation(ID_ANI_BOOMERANG_LEFT);
}

Boomerang::~Boomerang()
{
}

void Boomerang::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + BOOMERANG_BBOX_WIDTH;
	bottom = y + BOOMERANG_BBOX_HEIGTH;
}

void Boomerang::Render()
{
	int ani = nx > ITEM_RIGHT ? ITEM_RIGHT : ITEM_LEFT;
	animations[ani]->Render(x, y);
	RenderBoundingBox();
}

void Boomerang::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{
}
