#include "Dagger.h"

Dagger::Dagger(D3DXVECTOR2 position, int nx)
{
	this->x = position.x;
	this->y = position.y;
	this->nx = nx;
	vx = nx * DAGGER_SPEED_X;

	id = ID_DAGGER;

	AddAnimation(ID_ANI_DAGGER_LEFT);
	AddAnimation(ID_ANI_DAGGER_RIGHT);
}

Dagger::~Dagger()
{
}

void Dagger::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + DAGGER_BBOX_WIDTH;
	bottom = y + DAGGER_BBOX_HEIGHT;
}

void Dagger::Render()
{
	int ani = nx > 0 ? 0 : 1;
	animations[ani]->Render(x, y);
	RenderBoundingBox();
}
