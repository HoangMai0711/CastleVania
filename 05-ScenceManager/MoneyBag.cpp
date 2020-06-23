#include "MoneyBag.h"


MoneyBag::MoneyBag(D3DXVECTOR2 position, int id)
{
	this->x = position.x;
	this->y = position.y;
	this->id = id;

	showScoreStart = 0;

	switch (id)
	{
	case ID_RED_MONEYBAG:
		score = 100;
		break;
	case ID_BLUE_MONEYBAG:
		score = 400;
		break;
	case ID_YELLOW_MONEYBAG:
		score = 700;
		break;
	case ID_BIG_MONEYBAG:
		score = 1000;
	default:
		break;
	}

	AddAnimation(ID_ANI_RED_MONEYBAG);
	AddAnimation(ID_ANI_RED_MONEYBAG_SCORE);
	AddAnimation(ID_ANI_BLUE_MONEYBAG);
	AddAnimation(ID_ANI_BLUE_MONEYBAG_SCORE);
	AddAnimation(ID_ANI_YELLOW_MONEYBAG);
	AddAnimation(ID_ANI_YELLOW_MONEYBAG_SCORE);
	AddAnimation(ID_ANI_BIG_MONEYBAG);
	AddAnimation(ID_ANI_BIG_MONEYBAG_SCORE);
}

MoneyBag::~MoneyBag()
{
}

void MoneyBag::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (showScoreStart == 0) {
		left = x;
		top = y;
		right = x + MONEYBAG_BBOX_WIDTH;
		bottom = y + MONEYBAG_BBOX_HEIGHT;
	}
	else
		left = top = right = bottom = 0;
}

void MoneyBag::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{
	Items::Update(dt, objects);

	if (!isOnGround)
		vy += MONEYBAG_GRAVITY * dt;
	if (showScoreStart > 0)
		vy = 0;

	if (showScoreStart > 0 && GetTickCount() - showScoreStart > MONEYBAG_SHOW_SCORE_TIME)
		state = STATE_DESTROYED;
}

void MoneyBag::Render()
{
	int ani = -1;
	switch (id)
	{
	case ID_RED_MONEYBAG:
		if (showScoreStart == 0)
			ani = RED_MONEYBAG_ANI;
		else
			ani = RED_MONEYBAG_SCORE_ANI;
		break;
	case ID_BLUE_MONEYBAG:
		if (showScoreStart == 0)
			ani = BLUE_MONEYBAG_ANI;
		else
			ani = BLUE_MONEYBAG_SCORE_ANI;
		break;
	case ID_YELLOW_MONEYBAG:
		if (showScoreStart == 0)
			ani = YELLOW_MONEYBAG_ANI;
		else
			ani = YELLOW_MONEYBAG_SCORE_ANI;
		break;
	case ID_BIG_MONEYBAG:
		if (showScoreStart == 0)
			ani = BIG_MONEYBAG_ANI;
		else
			ani = BIG_MONEYBAG_SCORE_ANI;
		break;
	default:
		break;
	}
	animations[ani]->Render(x, y);
}

void MoneyBag::StartShowScore()
{
	showScoreStart = GetTickCount();
}
