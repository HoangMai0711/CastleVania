#pragma once

#include "Item.h"

#define MONEYBAG_BBOX_WIDTH			15
#define MONEYBAG_BBOX_HEIGHT		15
#define MONEYBAG_GRAVITY			0.0004f
#define MONEYBAG_SHOW_SCORE_TIME	1200

#define RED_MONEYBAG_ANI				0
#define RED_MONEYBAG_SCORE_ANI			1
#define BLUE_MONEYBAG_ANI				2
#define BLUE_MONEYBAG_SCORE_ANI			3
#define YELLOW_MONEYBAG_ANI				4
#define YELLOW_MONEYBAG_SCORE_ANI		5
#define BIG_MONEYBAG_ANI				6
#define BIG_MONEYBAG_SCORE_ANI			7
#define CROWN_ANI						8
#define CROWN_SCORE_ANI					9

class MoneyBag : public Item
{
	DWORD showScoreStart;
public:
	MoneyBag(D3DXVECTOR2 position, int id);
	~MoneyBag();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *nonGridObject, set<LPGAMEOBJECT> gridObject);
	virtual void Render();

	void StartShowScore();

	int GetScore() { return this->score; }
};

