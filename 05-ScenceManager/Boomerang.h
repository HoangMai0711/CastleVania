#pragma once

#include "Weapon.h"
#include "Simon.h"

#define BOOMERANG_BBOX_WIDTH		15
#define BOOMERANG_BBOX_HEIGTH		16

#define BOOMERANG_SPEED				0.12f
#define BOOMERANG_DISAPPEAR_TIME	1000

class Boomerang : public Weapon
{
protected:
	DWORD leaveStart;
	bool isBack;
public:
	Boomerang(D3DXVECTOR2 position, int nx);
	~Boomerang();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *objects);
};

