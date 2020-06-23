#include "HiddenObject.h"

HiddenObject::HiddenObject(D3DXVECTOR2 position, int reward, D3DXVECTOR2 rewardPos)
{
	x = position.x;
	y = position.y;
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
	r = x + HIDDEN_OBJ_BBOX_WIDTH;
	b = y + HIDDEN_OBJ_BBOX_HEIGHT;
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
		reward = new MoneyBag({ rewardPosition.x,rewardPosition.y }, rewardId);
		DebugOut(L"-----Create reward object ID = %d", rewardId);
		break;
	default:
		DebugOut(L"-----No ID = %d found", rewardId);
		break;
	}
	objects->push_back(reward);
	state = STATE_DESTROYED;
}
