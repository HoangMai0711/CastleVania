#pragma once

#include "GameObject.h"

#define STATIC_OBJ_STATE_NORMAL		0
#define STATIC_OBJ_STATE_HITTED		1

class StaticObjects : public CGameObject
{
public:
	StaticObjects();
	~StaticObjects();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	virtual void Render();
	virtual void IsHitted();
};

