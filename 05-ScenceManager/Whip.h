#pragma once

#include "Game.h"
#include "Weapon.h"

class Simon;

class Whip : public Weapon
{
	int level;
	int GetCurrentAnimation();
public:
	Whip();
	~Whip();

	void Update(DWORD dt, vector<LPGAMEOBJECT> *nonGridObject, set<LPGAMEOBJECT> gridObject, D3DXVECTOR2 playerPos, int playerNx);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Render();
	void Upgrade();
	void Degrade();

	void Load();
	int GetWhipLevel() { return level; }
	void SetWhipLevel(int lv) { this->level = lv; }
};

