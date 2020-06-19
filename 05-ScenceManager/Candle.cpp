#include "Candle.h"


Candle::Candle(D3DXVECTOR2 position, int reward)
{
	this->x = position.x;
	this->y = position.y;
	this->idReward = reward;
	id = ID_CANDLE;

	AddAnimation(ID_ANI_CANDLE);
}

Candle::~Candle()
{
}

void Candle::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (state == STATIC_OBJ_STATE_NORMAL) {
		left = x;
		top = y;
		right = left + CANDLE_BBOX_WIDTH;
		bottom = top + CANDLE_BBOX_HEIGHT;
	}
	else {
		left = top = right = bottom = 0;
	}
	//DebugOut("")
}
