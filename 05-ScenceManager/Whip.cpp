#include "Whip.h"



int Whip::GetCurrentAnimation()
{
	int ani = 0;
	if (level == 0 && nx > 0)
		ani = 0;
	else if (level == 0 && nx < 0)
		ani = 1;
	else if (level == 1 && nx > 0)
		ani = 2;
	else if (level == 1 && nx < 0)
		ani = 3;
	else if (level == 2 && nx > 0)
		ani = 4;
	else
		ani = 5;

	return ani;
}

Whip::Whip()
{
	id = ID_WHIP;
	vx = 0;
	vy = 0;
	level = 0;

	AddAnimation(ID_ANI_WHIP_SHORT_RIGHT);			// Level 1 Right - Ani ID: 0
	AddAnimation(ID_ANI_WHIP_SHORT_LEFT);			// Level 1 Left - Ani ID: 1
	AddAnimation(ID_ANI_WHIP_NORMAL_RIGHT);			// Level 2 Right - Ani ID: 2
	AddAnimation(ID_ANI_WHIP_NORMAL_LEFT);			// Level 2 Left - Ani ID: 3
	AddAnimation(ID_ANI_WHIP_LONG_RIGHT);			// Level 3 Right - Ani ID: 4
	AddAnimation(ID_ANI_WHIP_LONG_LEFT);			// Level 3 Left - Ani ID: 5
}


Whip::~Whip()
{
}

void Whip::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, D3DXVECTOR2 playerPos, int playerNx)
{
	DebugOut(L"[INFO]Simon attack Whip\n");
	
	Weapon::Update(dt, coObjects);

	this->x = playerPos.x;
	this->y = playerPos.y;
	this->nx = playerNx;
}

void Whip::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (animations[GetCurrentAnimation()]->GetCurrentFrame() == 2) {
		int width, height;

		switch (level) {
		case 0:
			width = WHIP_BBOX_WIDTH_SHORT;
			height = WHIP_BBOX_HEIGHT_SHORT;
			break;
		case 1:
			width = WHIP_BBOX_WIDTH_NORMAL;
			height = WHIP_BBOX_HEIGHT_NORMAL;
			break;
		case 2:
			width = WHIP_BBOX_WIDTH_LONG;
			height = WHIP_BBOX_HEIGHT_LONG;
			break;
		}
		left = x + animations[GetCurrentAnimation()]->GetFramePosition().x;
		top = y + animations[GetCurrentAnimation()]->GetFramePosition().y;
		right = left + height;
		bottom = top + width;
		//DebugOut(L"[INFO]L-T-R-B: %f-%f-%f-%f\n", left, top, right, bottom);
	}
	else {
		left = top = right = bottom = 0;
	}
	DebugOut(L"[INFO]Whip BBOX: %f-%f-%f-%f\n", left, top, right, bottom);
}

void Whip::Render()
{
	animations[GetCurrentAnimation()]->Render(x, y);

	if (animations[GetCurrentAnimation()]->GetCurrentFrame() == 2) {
		RenderBoundingBox();
	}
}

void Whip::Upgrade()
{
	if (level < 2)
		level++;
}
