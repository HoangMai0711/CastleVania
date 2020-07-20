#include "Enemy.h"


Enemy::Enemy()
{
	hitEffectStart = 0;
	untouchableStart = 0;
	AddAnimation(ID_ANI_HIT_EFFECT);
	AddAnimation(ID_ANI_ENEMY_HIDDEN);
}


Enemy::~Enemy()
{
}

void Enemy::Update(DWORD dt, vector<LPGAMEOBJECT> *nonGridObject, set<LPGAMEOBJECT> gridObject)
{
	CGameObject::Update(dt, nonGridObject, gridObject);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	vector<LPGAMEOBJECT> wallObjects;

	//DebugOut(L"---coobject size: %d\n", coObjects->size());

	for (auto i : gridObject) {
		if (i->GetId() == ID_WALL)
			wallObjects.push_back(i);
	}


	CalcPotentialCollisions(&wallObjects, coEvents);

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		//DebugOut(L"----No collision\n");
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		//DebugOut(L"-----ny: %f\n", ny);

		// block 
		x += min_tx * dx + nx * 0.11f;
		y += min_ty * dy + ny * 0.10f;

		if (ny != 0)
		{
			vx = 0;
			vy = 0;
			isOnGround = true;
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	coEvents.clear();

	if (untouchableStart > 0 && GetTickCount() - untouchableStart > ENEMY_UNTOUCHABLE_TIME)
		untouchableStart = 0;

	DWORD effectTimeCount = GetTickCount() - hitEffectStart;
	if (effectTimeCount > HIT_EFFECT_TIME && hitEffectStart > 0) {
		hitEffectStart = 0;

		if (health <= 0) {
			DebugOut(L"---Enemy health: %d\n", health);
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
			default:
				reward = NULL;
				break;
			}
			if (reward)
				nonGridObject->push_back(reward);
		}
	}
}

void Enemy::IsHitted()
{
	if (untouchableStart > 0)
		return;

	untouchableStart = GetTickCount();

	DecreaseHealth();
	SetSpeed(0, 0);
	hitEffectStart = GetTickCount();
	//state = ENEMY_STATE_HITTED;
}

void Enemy::DecreaseHealth()
{
	health -= 1;
	if (health < 0)
		health = 0;
}
