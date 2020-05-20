#include "StaticObjects.h"



StaticObjects::StaticObjects()
{
}


StaticObjects::~StaticObjects()
{
}

void StaticObjects::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{
}

void StaticObjects::Render()
{
	if (state == STATIC_OBJ_STATE_NORMAL)
		animations[0]->Render(x, y);
	//else
	//	animations[1]->Render(x, y);
}

void StaticObjects::IsHitted()
{
	DebugOut(L"----Object ID Hitted: %d\n", id);
	state = STATIC_OBJ_STATE_HITTED;
}
