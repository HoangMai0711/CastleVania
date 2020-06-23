#include "Boomerang.h"


Boomerang::Boomerang(D3DXVECTOR2 position, int nx)
{
	this->x = position.x;
	this->y = position.y;
	this->nx = nx;
	isBack = false;
	leaveStart = GetTickCount();

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
	Weapon::Update(dt, objects);

	if (leaveStart > 0 && GetTickCount() - leaveStart > BOOMERANG_DISAPPEAR_TIME)
	{
		leaveStart = 0;
		nx = -nx;
		vx = -vx;
		isBack = true;
	}
	if (isBack)
	{
		float sl, st, sr, sb, l, t, r, b;
		GetBoundingBox(l, t, r, b);

		Simon::GetInstance()->GetBoundingBox(sl, st, sr, sb);

		RECT A, B;
		A = { long(l),long(t),long(r),long(b) };
		B = { long(sl),long(st),long(sr),long(sb) };

		if (CGame::GetInstance()->IsColliding(A,B))
			state = STATE_DESTROYED;
	}
}
