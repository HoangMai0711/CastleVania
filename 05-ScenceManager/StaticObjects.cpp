#include "StaticObjects.h"



StaticObjects::StaticObjects()
{
	state = STATIC_OBJ_STATE_NORMAL;
	AddAnimation(ID_ANI_HIT_EFFECT);
	hitEffectStart = 0;
	//isDropped = false;
}


StaticObjects::~StaticObjects()
{
}

void StaticObjects::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{
	CGameObject::Update(dt);
	DWORD effectTimeCount = GetTickCount() - hitEffectStart;

	if (effectTimeCount > HIT_EFFECT_TIME && hitEffectStart > 0) {
		hitEffectStart = 0;
		state = STATE_DESTROYED;

		LPGAMEOBJECT reward;
		int rewardId = GetRewardId();

		switch (rewardId)
		{
		case ID_BIG_HEART:
			reward = new BigHeart({ x,y });
			break;
		case ID_WHIP_UPGRADE:
			reward = new WhipUpgrade({ x,y });
			break;
		case ID_DAGGER:
			reward = new ItemDagger({ x,y });
			break;
		case ID_ITEM_BOOMERANG:
			reward = new ItemBoomerang({ x,y });
			break;
		case ID_SMALL_HEART:
			reward = new SmallHeart({ x,y });
			break;
		case ID_RED_MONEYBAG:
			reward = new MoneyBag({ x,y }, rewardId);
			break;
		case ID_BLUE_MONEYBAG:
			reward = new MoneyBag({ x,y }, rewardId);
			break;
		case ID_YELLOW_MONEYBAG:
			reward = new MoneyBag({ x,y }, rewardId);
			break;
		case ID_BIG_MONEYBAG:
			reward = new MoneyBag({ x,y }, rewardId);
			break;
		default:
			reward = NULL;
			break;
		}
		objects->push_back(reward);
	}
}

void StaticObjects::Render()
{
	if (state == STATIC_OBJ_STATE_HITTED || state == STATE_DESTROYED)
		animations[0]->Render(x, y);
	else
		animations[1]->Render(x, y);
}

void StaticObjects::IsHitted()
{
	hitEffectStart = GetTickCount();
	state = STATIC_OBJ_STATE_HITTED;
}
