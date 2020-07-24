#include "HiddenObject.h"

HiddenObject::HiddenObject(D3DXVECTOR2 position, int reward, D3DXVECTOR2 rewardPos, int width, int height)
{
	x = position.x;
	y = position.y;
	this->width = width;
	this->height = height;
	
	rewardPosition = rewardPos;

	id = ID_HIDDEN_OBJECTS;
	this->idReward = reward;

	state = 16527;
}

HiddenObject::~HiddenObject()
{
}

void HiddenObject::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}

void HiddenObject::Render()
{
	RenderBoundingBox();
}

void HiddenObject::IsCollide(vector<LPGAMEOBJECT>* objects)
{
	LPGAMEOBJECT reward;
	int rewardId = GetRewardId();

	switch (rewardId)
	{
	case ID_BIG_MONEYBAG:
		reward = new MoneyBag({ rewardPosition.x, rewardPosition.y }, rewardId);
		DebugOut(L"-----Create reward object ID = %d\n", rewardId);
		break;
	case ID_CROWN:
		reward = new MoneyBag({ rewardPosition.x, rewardPosition.y }, rewardId);
		break;
	default:
		reward = NULL;
		break;
	}
	if (reward)
		objects->push_back(reward);
	state = STATE_DESTROYED;
}
