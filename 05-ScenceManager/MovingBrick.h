#pragma once
#include "GameObject.h"
#include "Game.h"

#define MOVING_BRICK_BBOX_WIDTH			31
#define MOVING_BRICK_BBOX_HEIGHT		7

#define MOVING_BRICK_SPEED				0.033f

class MovingBrick :
	public CGameObject
{
public:
	MovingBrick(D3DXVECTOR2 position);
	~MovingBrick();

	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *nonGridObject, set<LPGAMEOBJECT> gridObject);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

