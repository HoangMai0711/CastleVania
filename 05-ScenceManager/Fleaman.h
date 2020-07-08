#pragma once

#include "Enemy.h"

#define FLEAMAN_BBOX_WIDTH		16
#define FLEAMAN_BBOX_HEIGHT		16

#define FLEAMAN_ANI_JUMP_RIGHT	1
#define FLEAMAN_ANI_JUMP_LEFT	2
#define FLEAMAN_ANI_PREATTACK	3
#define FLEAMAN_ANI_IDLE_RIGHT	4
#define FLEAMAN_ANI_IDLE_LEFT	5

#define FLEAMAN_STATE_PREATTACK	4
#define FLEAMAN_STATE_ATTACK	5

#define FLEAMAN_ACTIVE_DISTANCE_WIDTH		60

#define FLEAMAN_GRAVITY					0.0006f
#define FLEAMAN_SPEED_Y_ATTACK			0.1f
#define FLEAMAN_SPEED_Y_NORMAL			0.08f
#define FLEAMAN_SPEED_X					0.08f
#define FLEAMAN_TIME_JUMP_ON_GROUND		400
#define FLEAMAN_TIME_ATTACK				800

class Fleaman :
	public Enemy
{
	DWORD firstJumpStart;
	DWORD jumpOnGroundStart;
	DWORD attackStart;
	DWORD onGroundStart;

	bool isJumping;
	bool isStartAttack;
	bool isActive;
	bool isFirstJump;
public:
	Fleaman(D3DXVECTOR2 position);
	~Fleaman();

	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *nonGridObject, set<LPGAMEOBJECT> gridObject);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	void SetState(int state);
	void StartActive();
};