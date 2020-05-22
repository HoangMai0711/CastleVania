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
		/*if (GetRewardId() == ID_BIG_HEART && !isDropped) {
			LPGAMEOBJECT reward = new BigHeart({ x,y });
			objects->push_back(reward);
			isDropped = TRUE;
		}*/
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
		default:
			reward = NULL;
			break;
		}
		objects->push_back(reward);
	}
}

void StaticObjects::Render()
{
	if (state == STATIC_OBJ_STATE_HITTED || state==STATE_DESTROYED)
		animations[0]->Render(x, y);
	else
		animations[1]->Render(x, y);
}

void StaticObjects::IsHitted()
{
	hitEffectStart = GetTickCount();
	DebugOut(L"------Hit effect time: %d\n", hitEffectStart);
	DebugOut(L"----Object ID Hitted: %d\n", id);
	state = STATIC_OBJ_STATE_HITTED;
}
