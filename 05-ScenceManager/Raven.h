#pragma once

#include "Enemy.h"

#define RAVEN_BBOX_WIDTH		16
#define RAVEN_BBOX_HEIGHT		16

#define RAVEN_ANI_IDLE_RIGHT	1
#define RAVEN_ANI_IDLE_LEFT		2
#define RAVEN_ANI_FLY_RIGHT		3
#define RAVEN_ANI_FLY_LEFT		4

#define RAVEN_ACTIVE_DISTANCE_WIDTH		94
#define RAVEN_ACTIVE_DISTANCE_HEIGHT	80

#define RAVEN_TIME_IDLE			350
#define RAVEN_TIME_FLY			400

#define RAVEN_STATE_FLY			10

class Raven :
	public Enemy
{
	DWORD idleStart;
	DWORD flyStart;
	bool isActive;

	D3DXVECTOR2 firstPos;
public:
	Raven(D3DXVECTOR2 position);
	~Raven();

	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *nonGridObject, set<LPGAMEOBJECT> gridObject);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

