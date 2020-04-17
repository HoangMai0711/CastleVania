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

	virtual void GetBoundingBox(float &left, float &top, float &bottom);
	virtual void Render();
	void Upgrade();
};

