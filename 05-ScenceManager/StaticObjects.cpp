#include "StaticObjects.h"



StaticObjects::StaticObjects()
{
	state = STATIC_OBJ_STATE_NORMAL;
	AddAnimation(ID_ANI_HIT_EFFECT);
	hitEffectStart = 0;
}


StaticObjects::~StaticObjects()
{
}

void StaticObjects::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{
	if (hitEffectStart > 300) {
		hitEffectStart = 0;
	}
}

void StaticObjects::Render()
{
	if (state == STATIC_OBJ_STATE_HITTED)
		animations[0]->Render(x, y);
	else
		animations[1]->Render(x, y);
}

void StaticObjects::IsHitted()
{
	hitEffectStart = GetTickCount();
	DebugOut(L"----Object ID Hitted: %d\n", id);
	state = STATIC_OBJ_STATE_HITTED;
}
