#pragma once

#include "StaticObjects.h"

#define CANDLE_BBOX_WIDTH		8
#define CANDLE_BBOX_HEIGHT		15

class Candle : public StaticObjects
{
public:
	Candle(D3DXVECTOR2 position, int reward);
	~Candle();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

