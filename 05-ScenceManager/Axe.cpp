#include "Axe.h"



Axe::Axe(D3DXVECTOR2 position, int nx)
{
	this->x = position.x;
	this->y = position.y;
	this->nx = nx;
	vx = AXE_SPEED_X;
	vy = -AXE_SPEED_Y;

	id = ID_AXE;

	AddAnimation(ID_ANI_AXE_RIGHT);
	AddAnimation(ID_ANI_AXE_LEFT);
}

Axe::~Axe()
{
}

void Axe::Render()
{
	int ani;
	if (nx > 0)
		ani = AXE_ANI_RIGHT;
	else
		ani = AXE_ANI_LEFT;
	//DebugOut(L"------render axe ani: %d\n", ani);
	animations[ani]->Render(x, y);
}

void Axe::Update(DWORD dt, vector<LPGAMEOBJECT> *nonGridObject, set<LPGAMEOBJECT> gridObject)
{
	vx = nx * AXE_SPEED_X;
	vy += AXE_GRAVITY * dt;

	Weapon::Update(dt, nonGridObject, gridObject);
}

void Axe::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + AXE_BBOX_WIDTH;
	bottom = y + AXE_BBOX_HEIGHT;
}
