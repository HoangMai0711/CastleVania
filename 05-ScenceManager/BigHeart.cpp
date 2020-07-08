#include "BigHeart.h"

BigHeart::BigHeart(D3DXVECTOR2 position)
{
	this->x = position.x;
	this->y = position.y;
	id = ID_BIG_HEART;

	AddAnimation(ID_ANI_BIG_HEART);
}

BigHeart::~BigHeart()
{
}

void BigHeart::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + BIG_HEART_BBOX_WIDTH;
	bottom = y + BIG_HEART_BBOX_HEIGHT;
}

void BigHeart::Update(DWORD dt, vector<LPGAMEOBJECT> *nonGridObject, set<LPGAMEOBJECT> gridObject)
{
	Items::Update(dt, nonGridObject, gridObject);

	if (!isOnGround)
		vy += BIG_HEART_GRAVITY * dt;
}
