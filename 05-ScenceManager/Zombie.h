#pragma once

#include "Enemy.h"

#define ZOMBIE_BBOX_WIDTH		15
#define ZOMBIE_BBOX_HEIGHT		30

#define ZOMBIE_SPEED_X			0.025f	
#define ZOMBIE_GRAVITY			0.0006f

#define ZOMBIE_ANI_WALK_RIGHT	2
#define ZOMBIE_ANI_WALK_LEFT	3

class Zombie :
	public Enemy
{

public:
	Zombie(D3DXVECTOR2 position, int nx, int reward);
	~Zombie();

	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *nonGridObject, set<LPGAMEOBJECT> gridObject);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

