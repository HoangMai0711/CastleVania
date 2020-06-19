#pragma once

#include "GameObject.h"
#include "Simon.h"
#include "SmallHeart.h"

#define ENEMY_STATE_HITTED		0
#define ENEMY_STATE_IDLE		1
#define ENEMY_STATE_ACTIVE		2

#define ENEMY_ANI_HITTED		0

class Enemy : public CGameObject
{
protected:
	int health;
	DWORD hitEffectStart;
public:
	Enemy();
	~Enemy();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	virtual void IsHitted();
	virtual void DecreaseHealth();
	int GetHealth() { return health; }
};

