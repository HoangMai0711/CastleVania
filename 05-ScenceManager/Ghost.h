#pragma once

#include "Enemy.h"

#define GHOST_STATE_HIDDEN			5

#define GHOST_BBOX_WIDTH			16
#define GHOST_BBOX_HEIGHT			16

#define GHOST_SPEED_X				0.07f
#define GHOST_SPEED_Y				0.06f

#define GHOST_ANI_HIDDEN			3
#define GHOST_ANI_FLY_RIGHT			1
#define GHOST_ANI_FLY_LEFT			2

#define GHOST_DISTANCE_TO_SIMON		50

class Ghost :
	public Enemy
{
protected:
	bool isActive;
public:
	Ghost(D3DXVECTOR2 position);
	~Ghost();

	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

