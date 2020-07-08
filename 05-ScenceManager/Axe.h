#pragma once

#include "Weapon.h"

#define AXE_BBOX_WIDTH		16
#define AXE_BBOX_HEIGHT		16

#define AXE_SPEED_X			0.09f
#define AXE_SPEED_Y			0.22f
#define AXE_GRAVITY			0.0005f

#define AXE_ANI_RIGHT		0
#define AXE_ANI_LEFT		1

class Axe :
	public Weapon
{
public:
	Axe(D3DXVECTOR2 position, int nx);
	~Axe();

	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *nonGridObject, set<LPGAMEOBJECT> gridObject);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

