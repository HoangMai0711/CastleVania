#include "CrystalBall.h"



CrystalBall::CrystalBall(D3DXVECTOR2 position)
{
	this->x = position.x;
	this->y = position.y;

	id = ID_CRYSTAL_BALL;

	AddAnimation(ID_ANI_CRYSTAL_BALL);
}


CrystalBall::~CrystalBall()
{
}

void CrystalBall::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + CRYSTAL_BALL_BBOX_WIDTH;
	bottom = y + CRYSTAL_BALL_BBOX_HEIGHT;
}

void CrystalBall::Update(DWORD dt, vector<LPGAMEOBJECT>* nonGridObject, set<LPGAMEOBJECT> gridObject)
{
	Item::Update(dt, nonGridObject, gridObject);

	if (!isOnGround)
		vy += CRYSTAL_BALL_GRAVITY * dt;

	disappearStart = 0;
}
