#pragma once

#include "Enemy.h"

#define FLEAMAN_BBOX_WIDTH		16
#define FLEAMAN_BBOX_HEIGHT		16

#define FLEAMAN_ANI_IDLE_RIGHT	1
#define FLEAMAN_ANI_IDLE_LEFT	2
#define FLEAMAN_ANI_PREATTACK	3

#define FLEAMAN_STATE_PREATTACK	3

class Fleaman :
	public Enemy
{
public:
	Fleaman(D3DXVECTOR2 position);
	~Fleaman();

	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

