#pragma once

#include "Enemy.h"

#define BLACK_KNIGHT_BBOX_WIDTH		15
#define BLACK_KNIGHT_BBOX_HEIGHT	32

#define BLACK_KNIGHT_WALKING_SPEED	0.03f

#define BLACK_KNIGHT_ANI_WALKING_RIGHT	1
#define BLACK_KNIGHT_ANI_WALKING_LEFT	2

class BlackKnight :
	public Enemy
{
protected:
	float edgeLeft;
	int edgeRight;
public:
	BlackKnight(D3DXVECTOR2 position, int nx, int idReward, int edge);
	~BlackKnight();

	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

