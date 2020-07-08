#pragma once

#include "TransparentObjects.h"
#include "Simon.h"
#include "Zombie.h"

#define NUMBER_OF_ZOMBIE		3
#define DELAY_TIME				3000
#define TIME_BORN				800

class ZombieZone :
	public TransparentObjects
{
	int width;
	int height;
	float zombiePosY;
	int numOfZombie;
	int zombieId;

	int currentIter;
	bool isActive;
	DWORD delayStart;

	bool firstSpawn;

	void SpawnEnemy(vector<LPGAMEOBJECT>* objects);
public:
	ZombieZone(D3DXVECTOR2 position, int width, int height, int y);
	~ZombieZone();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *nonGridObject, set<LPGAMEOBJECT> gridObject);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

