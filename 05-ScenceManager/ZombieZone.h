#pragma once

#include "TransparentObjects.h"
#include "Simon.h"
#include "Zombie.h"

#define SPAWN_TIME				6000

class ZombieZone :
	public TransparentObjects
{
	DWORD spawStart;
	int numOfZombie;
	int currentNumZombie;

	int width;
	int height;
public:
	ZombieZone(D3DXVECTOR2 position, int width, int height);
	~ZombieZone();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *nonGridObject, set<LPGAMEOBJECT> gridObject);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

