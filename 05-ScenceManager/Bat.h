#pragma once

#include "Enemy.h"

#define BAT_ANI_IDLE		1
#define BAT_ANI_FLY			2

#define BAT_BBOX_WIDTH		18
#define BAT_BBOX_HEIGHT		16

#define BAT_SPEED_X			0.04f
#define BAT_SPEED_y			0.07f
#define BAT_TIME_FLYDOWN	450

#define BAT_FLY_DOWN		10
#define BAT_FLY_NORMAL		11

#define BAT_ACTIVE_DISTANCE_WIDTH	99
#define BAT_ACTIVE_DISTANCE_HEIGHT	38

class Bat :
	public Enemy
{
protected:
	int originX;
	int originY;
	int delta;
	DWORD startFlyDown;
	bool isActive = false;
public:
	Bat(D3DXVECTOR2 position, int width, int reward);
	~Bat();

	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	
	void SetState(int state);
};

