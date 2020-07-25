#pragma once

#include "Enemy.h"

#define BLACK_KNIGHT_BBOX_WIDTH		15
#define BLACK_KNIGHT_BBOX_HEIGHT	32

#define BLACK_KNIGHT_WALKING_SPEED	0.015f

#define BLACK_KNIGHT_ANI_WALKING_RIGHT	2
#define BLACK_KNIGHT_ANI_WALKING_LEFT	3

class BlackKnight :
	public Enemy
{
protected:
	float edgeLeft;
	int edgeRight;

	int firstEdge;
	D3DXVECTOR2 firstPos;
public:
	BlackKnight(D3DXVECTOR2 position, int nx, int idReward, int edge);
	~BlackKnight();

	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *nonGridObject, set<LPGAMEOBJECT> gridObject);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	//void IsHitted();
};

