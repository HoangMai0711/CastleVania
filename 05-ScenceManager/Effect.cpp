#include "Effect.h"



Effect::Effect()
{
	effectTime = GetTickCount();
}


Effect::~Effect()
{
}

void Effect::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = top = right = bottom = 0;
}

void Effect::Update(DWORD dt, vector<LPGAMEOBJECT>* nonGridObject, set<LPGAMEOBJECT> gridObject)
{
	for (int i = 0; i < totalEffect; i++)
	{
		x[i] += vx[i] * dt;
		y[i] += vy[i] * dt;
		vy[i] += EFFECT_GRAVITY * dt;
	}

	if (GetTickCount() - effectTime > EFFECT_TIME)
		state = STATE_DESTROYED;
}

void Effect::Render()
{
	for (int i = 0; i < totalEffect; i++)
		animations[0]->Render(x[i], y[i]);
}
