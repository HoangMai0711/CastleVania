#include "BreakableBrickEffect.h"



BreakableBrickEffect::BreakableBrickEffect(D3DXVECTOR2 position)
{
	totalEffect = 4;

	x = new float[totalEffect];
	y = new float[totalEffect];
	vx = new float[totalEffect];
	vy = new float[totalEffect];

	for (int i = 0; i < totalEffect; i++)
	{
		x[i] = position.x;
		y[i] = position.y;
	}

	vx[0] = 0.03f;
	vx[1] = 0.008f;
	vx[2] = -0.02f;
	vx[3] = -0.01f;

	vy[0] = -0.07f;
	vy[1] = -0.1f;
	vy[2] = -0.05f;
	vy[3] = -0.02f;

	AddAnimation(ID_ANI_BRICK_EFFECT);
	AddAnimation(ID_ANI_BRICK_EFFECT);
	AddAnimation(ID_ANI_BRICK_EFFECT);
	AddAnimation(ID_ANI_BRICK_EFFECT);
}


BreakableBrickEffect::~BreakableBrickEffect()
{
}
