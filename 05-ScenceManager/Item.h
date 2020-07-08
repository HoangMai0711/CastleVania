#pragma once

#include "GameObject.h"

#define ITEM_DISAPPEAR_TIME		5000

class Item : public CGameObject
{
protected:
	DWORD disappearStart;
public:
	Item();
	~Item();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *nonGridObject, set<LPGAMEOBJECT> gridObject);

	void StartDisappear();
};

