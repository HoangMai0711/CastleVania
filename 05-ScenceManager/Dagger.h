#pragma once
#include "Weapon.h"

#define DAGGER_BBOX_WIDTH		18
#define DAGGER_BBOX_HEIGHT		10
#define DAGGER_SPEED_X			0.2f

class Dagger : public Weapon
{
public:
	Dagger(D3DXVECTOR2 position, int nx);
	~Dagger();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Render();
};

