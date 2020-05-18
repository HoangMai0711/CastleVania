#pragma once

#include "GameObject.h"

class Weapon : public CGameObject
{
public:
	Weapon();
	~Weapon();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
};

