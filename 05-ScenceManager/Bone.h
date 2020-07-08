#pragma once

#include "GameObject.h"
#include "Game.h"

#define BONE_BBOX_WIDTH		16
#define BONE_BBOX_HEIGHT	16

#define BONE_SPEED_X		0.003f
#define BONE_GRAVITY		0.0006f

class Bone :
	public CGameObject
{
public:
	Bone(D3DXVECTOR2 position, int nx);
	~Bone();

	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *nonGridObject, set<LPGAMEOBJECT> gridObject);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	float RandomFloat(float a, float b);
};

