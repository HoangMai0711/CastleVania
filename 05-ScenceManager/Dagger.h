#pragma once
#include "Weapon.h"

#define DAGGER_BBOX_WIDTH		18
#define DAGGER_BBOX_HEIGHT		10
#define DAGGER_SPEED_X			0.18f

class Dagger : public Weapon
{
public:
	Dagger(D3DXVECTOR2 position, int nx);
	~Dagger();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Render();
};

