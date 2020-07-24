#include "MovingBrick.h"


MovingBrick::MovingBrick(D3DXVECTOR2 position)
{
	this->x = position.x;
	this->y = position.y;
	id = ID_MOVING_BRICK;
	vx = MOVING_BRICK_SPEED;

	AddAnimation(ID_ANI_MOVING_BRICK);
}

MovingBrick::~MovingBrick()
{
}

void MovingBrick::Render()
{
	//DebugOut(L"-----Render Moving brick\n");
	animations[0]->Render(x,y);
	RenderBoundingBox();
}

void MovingBrick::Update(DWORD dt, vector<LPGAMEOBJECT> *nonGridObject, set<LPGAMEOBJECT> gridObject)
{
	float al, at, ar, ab;
	float bl, bt, br, bb;

	al = CGame::GetInstance()->GetCamPosX();
	at = CGame::GetInstance()->GetCamPosY();

	ar = al + SCREEN_WIDTH;
	ab = at + SCREEN_HEIGHT;

	GetBoundingBox(bl, bt, br, bb);

	RECT A, B;
	A = { long(al),long(at),long(ar),long(ab) };
	B = { long(bl),long(bt),long(br),long(bb) };

	if (!CGame::GetInstance()->IsColliding(A, B))
		return;

	CGameObject::Update(dt, nonGridObject, gridObject);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	vector<LPGAMEOBJECT> wallObjects;

	//DebugOut(L"---coobject size: %d\n", coObjects->size());

	for (auto i : gridObject) {
		if (i->GetId() == ID_WALL)
			wallObjects.push_back(i);
	}


	CalcPotentialCollisions(&wallObjects, coEvents);

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		//DebugOut(L"----No collision\n");
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		//DebugOut(L"-----ny: %f\n", ny);

		// block 
		//y += min_ty * dy + ny * 0.4f;
		vx = -vx;
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	coEvents.clear();
}

void MovingBrick::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + MOVING_BRICK_BBOX_WIDTH;
	bottom = y + MOVING_BRICK_BBOX_HEIGHT;
}
