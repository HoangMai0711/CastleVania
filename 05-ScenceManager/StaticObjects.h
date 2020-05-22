#pragma once

#include "GameObject.h"
#include "Items.h"
#include "BigHeart.h"
#include "WhipUpgrade.h"
#include "ItemDagger.h"

#define STATIC_OBJ_STATE_NORMAL		0
#define STATIC_OBJ_STATE_HITTED		1

#define HIT_EFFECT_TIME				450

class StaticObjects : public CGameObject
{
	DWORD hitEffectStart;
	bool isDropped;
public:
	StaticObjects();
	~StaticObjects();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	virtual void Render();
	virtual void IsHitted();

	int GetHitEffectTime() { return hitEffectStart; }
};

