#include "Item.h"



Item::Item()
{
	disappearStart = 0;
}


Item::~Item()
{
}

void Item::Render()
{
	animations[0]->Render(x, y);
}

void Item::Update(DWORD dt, vector<LPGAMEOBJECT>* nonGridObject, set<LPGAMEOBJECT> gridObject)
{
	//DebugOut(L"[INFO] Item update\n");
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
		y += min_ty * dy + ny * 0.4f;

		if (ny != 0)
		{
			vx = 0;
			vy = 0;
			isOnGround = true;
			StartDisappear();
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	coEvents.clear();

	if (GetTickCount() - disappearStart > ITEM_DISAPPEAR_TIME && disappearStart > 0)
		SetState(STATE_DESTROYED);
}

void Item::StartDisappear()
{
	disappearStart = GetTickCount();
}
