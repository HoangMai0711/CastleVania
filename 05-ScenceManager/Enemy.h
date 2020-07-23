#pragma once

#include "GameObject.h"
#include "Simon.h"

#define ENEMY_STATE_DIE			0
#define ENEMY_STATE_IDLE		1
#define ENEMY_STATE_ACTIVE		2
#define ENEMY_STATE_HIDDEN		3

#define ENEMY_ANI_HITTED		0
#define ENEMY_ANI_HIDDEN		1

#define ENEMY_UNTOUCHABLE_TIME			700

class Enemy : public CGameObject
{
protected:
	int health;
	DWORD hitEffectStart;
	DWORD untouchableStart;
public:
	Enemy();
	~Enemy();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *nonGridObject, set<LPGAMEOBJECT> gridObject);
	virtual void IsHitted(vector<LPGAMEOBJECT> *nonGridObject);
	virtual void DecreaseHealth();
	int GetHealth() { return health; }
};

