#pragma once

#include "GameObject.h"
#include "Simon.h"

#define PHANTOM_BAT_BBOX_WIDTH		50
#define PHANTOM_BAT_BBOX_HEIGHT		25

#define PHANTOM_BAT_STATE_IDLE		0
#define PHANTOM_BAT_STATE_ACTIVE	1
#define PHANTOM_BAT_STATE_DIE		2

#define PHANTOM_BAT_ANI_IDLE			0
#define PHANTOM_BAT_ANI_ACTIVE			1
#define PHANTOM_BAT_ANI_DIE				2
#define PHANTOM_BAT_ANI_DAMAGED			3

#define PHANTOM_X_START			515
#define PHANTOM_X_END			700
#define PHANTOM_Y_START			20
#define PHANTOM_Y_END			120

#define PHANTOM_TIME_IDLE					1500
#define PHANTOM_TIME_ATTACK					1200
#define PHANTOM_BAT_TIME_UNTOUCHABLE		500
#define PHANTOM_BAT_TIME_DIE				1000
#define PHANTOM_BAT_TIME_DAMAGED			500
#define PHANTOM_BAT_TIME_DEFLECT			100
#define PHANTOM_BAT_TIME_BACK				1200

class PhantomBat :
	public CGameObject
{
protected:
	DWORD idleStart;
	DWORD attackStart;
	DWORD untouchableStart;
	DWORD damagedStart;
	DWORD deflectStart;
	DWORD backStart;
	DWORD hittedStart;

	float originalX;
	float originalY;
public:
	PhantomBat(D3DXVECTOR2 position);
	~PhantomBat();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *nonGridObject, set<LPGAMEOBJECT> gridObject);
	virtual void Render();

	void IsHitted();
	void Reset();
};

