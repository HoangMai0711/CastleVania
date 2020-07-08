#include "SmallHeart.h"


SmallHeart::SmallHeart(D3DXVECTOR2 position)
{
	this->x = position.x;
	this->originX = position.x;
	this->y = position.y;
	AddAnimation(ID_ANI_SMALL_HEART);
	id = ID_SMALL_HEART;
	delta = 0;
}

SmallHeart::~SmallHeart()
{
}

void SmallHeart::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + SMALL_HEART_BBOX_WIDTH;
	bottom = y + SMALL_HEART_BBOX_HEIGHT;
}

void SmallHeart::Update(DWORD dt, vector<LPGAMEOBJECT> *nonGridObject, set<LPGAMEOBJECT> gridObject)
{
	if (!isOnGround)
	{
		vy += SMALL_HEART_GRAVITY;
		delta += SMALL_HEART_DELTA_X;
		x = sin(delta) * SMALL_HEART_AMPLITUDE_X + originX;
	}

	Items::Update(dt, nonGridObject, gridObject);
}
