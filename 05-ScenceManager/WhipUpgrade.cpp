#include "WhipUpgrade.h"


WhipUpgrade::WhipUpgrade(D3DXVECTOR2 postition)
{
	this->x = postition.x;
	this->y = postition.y;

	id = ID_WHIP_UPGRADE;
	AddAnimation(ID_ANI_WHIP_UPGRADE);

}

WhipUpgrade::~WhipUpgrade()
{
}

void WhipUpgrade::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + WHIP_UPGRADE_BBOX_WIDTH;
	bottom = y + WHIP_UPGRADE_BBOX_HEIGHT;
}

void WhipUpgrade::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Items::Update(dt, coObjects);

	if (!isOnGround) {
		DebugOut(L"----whip item isOnGround: FALSE\n");
		vy += WHIP_UPGRADE_GRAVITY * dt;
		DebugOut(L"----WHIP vy: %f\n", vy);
	}
}
