#pragma once

#include "Weapon.h"

class Simon;

class Whip : public Weapon
{
	int level;
	int GetCurrentAnimation();
public:
	Whip();
	~Whip();

	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects, D3DXVECTOR2 playerPos, int playerNx);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Render();
	void Upgrade();
};

