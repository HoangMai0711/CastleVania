#include "Brick.h"


CBrick::CBrick(D3DXVECTOR2 position, int reward)
{
	this->x = position.x;
	this->y = position.y;
	this->idReward = reward;

	state = STATIC_OBJ_STATE_NORMAL;
	isBroken = false;

	this->id = ID_BRICK;

	AddAnimation(ID_ANI_BRICK);
}

void CBrick::Render()
{
	if (state != STATIC_OBJ_STATE_NORMAL)
		animations[1]->Render(x, y);
}

void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* nonGridObject, set<LPGAMEOBJECT> gridObject)
{
	CGameObject::Update(dt, nonGridObject, gridObject);

	if (!isBroken && state == STATIC_OBJ_STATE_HITTED) {
		isBroken = true;
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
		case ID_ITEM_AXE:
			reward = new ItemAxe({ x,y });
			break;
		default:
			reward = NULL;
			break;
		}
		nonGridObject->push_back(reward);
	}
}


void CBrick::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + BRICK_BBOX_WIDTH;
	bottom = y + BRICK_BBOX_HEIGHT;
}

void CBrick::IsHitted()
{
	state = STATIC_OBJ_STATE_HITTED;
}