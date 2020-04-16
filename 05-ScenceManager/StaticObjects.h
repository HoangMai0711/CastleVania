#pragma once

#include "GameObject.h"

class StaticObjects : public CGameObject
{
public:
	StaticObjects();
	~StaticObjects();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	virtual void Render();
	virtual void IsHitted();
};

