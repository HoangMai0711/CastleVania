#pragma once

#include "GameObject.h"

#define EFFECT_GRAVITY		0.00025f

#define EFFECT_TIME	2000

class Effect :
	public CGameObject
{
protected:
	float* x;
	float* y;
	float* vx;
	float* vy;

	int totalEffect;
	DWORD effectTime;
public:
	Effect();
	~Effect();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *nonGridObject, set<LPGAMEOBJECT> gridObject);
	virtual void Render();
};

