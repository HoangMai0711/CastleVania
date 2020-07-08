#pragma once

#include "GameObject.h"
#include "Game.h"

class Weapon : public CGameObject
{
public:
	Weapon();
	~Weapon();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *nonGridObject, set<LPGAMEOBJECT> gridObject);
};
typedef Weapon* LPWEAPON;

