#include "Brick.h"


CBrick::CBrick(D3DXVECTOR2 position, int reward, int idAni)
{
	this->x = position.x;
	this->y = position.y;
	this->idReward = reward;

	state = STATIC_OBJ_STATE_NORMAL;
	isBroken = false;

	this->id = ID_BRICK;

	AddAnimation(idAni);
}

CBrick::~CBrick()
{
}

void CBrick::Render()
{
	if (state == STATIC_OBJ_STATE_NORMAL)
		animations[1]->Render(x, y);
}

void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* nonGridObject, set<LPGAMEOBJECT> gridObject)
{
	CGameObject::Update(dt, nonGridObject, gridObject);
}


void CBrick::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + BRICK_BBOX_WIDTH;
	bottom = y + BRICK_BBOX_HEIGHT;
}

void CBrick::IsHitted(vector<LPGAMEOBJECT> *nonGridObject)
{
	if (!isBroken) {
		isBroken = true;
		state = STATE_DESTROYED;
		LPGAMEOBJECT reward;
		int rewardId = GetRewardId();

		switch (rewardId)
		{
		case ID_DOUBLE_SHOT:
			reward = new MultishotItem({ x,y }, rewardId);
			break;
		case ID_TRIPLE_SHOT:
			reward = new MultishotItem({ x,y }, rewardId);
			break;
		case ID_POT_ROAST:
			reward = new PotRoast({ x,y });
			break;
		default:
			reward = NULL;
			break;
		}
		if (reward)
			nonGridObject->push_back(reward);

		float ex, ey;
		GetPosition(ex, ey);
		BreakableBrickEffect* effect = new BreakableBrickEffect({ ex, ey });
		nonGridObject->push_back(effect);
	}
}