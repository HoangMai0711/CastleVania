#pragma once

#include "Enemy.h"

#define GHOST_BBOX_WIDTH			16
#define GHOST_BBOX_HEIGHT			16

#define GHOST_SPEED_X				0.05f
#define GHOST_SPEED_Y				0.03f

#define GHOST_ANI_FLY_RIGHT			2
#define GHOST_ANI_FLY_LEFT			3

#define GHOST_DISTANCE_TO_SIMON_WIDTH	50
#define GHOST_DISTANCE_TO_SIMON_HEIGHT	5
#define GHOST_ACTIVE_DISTANCE_WIDTH		100
#define GHOST_ACTIVE_DISTANCE_HEIGHT	30

class Ghost :
	public Enemy
{
protected:
	bool isActive;

	D3DXVECTOR2 firstPos;
public:
	Ghost(D3DXVECTOR2 position);
	~Ghost();

	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *nonGridObject, set<LPGAMEOBJECT> gridObject);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Reset();
};

