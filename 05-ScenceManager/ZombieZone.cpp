#include "ZombieZone.h"


ZombieZone::ZombieZone(D3DXVECTOR2 position, int width, int height)
{
	this->x = position.x;
	this->y = position.y;
	this->width = width;
	this->height = height;

	id = ID_ZOMBIE_ZONE;

	spawStart = 0;
}

ZombieZone::~ZombieZone()
{
}

void ZombieZone::Update(DWORD dt, vector<LPGAMEOBJECT> *nonGridObject, set<LPGAMEOBJECT> gridObject)
{
	if (spawStart > 0 && GetTickCount() - spawStart > SPAWN_TIME) {
		spawStart = 0;
	}

	float sl, st, sr, sb, l, t, r, b;
	Simon::GetInstance()->GetBoundingBox(sl, st, sr, sb);
	GetBoundingBox(l, t, r, b);
	int simonNx = Simon::GetInstance()->GetNx();

	CGame* camPosition = CGame::GetInstance();

	if (CGame::GetInstance()->IsColliding({ long(sl),long(st),long(sr),long(sb) },
		{ long(l), long(t), long(r), long(b) }))
	{
		if (spawStart == 0) {
			numOfZombie = 3;
			spawStart = GetTickCount();

			for (int i = 0; i < numOfZombie; i++) {
				int cl = camPosition->GetCamPosX();
				int ct = camPosition->GetCamPosY();
				int cr = cl + SCREEN_WIDTH;
				int cb = ct + SCREEN_HEIGHT;

				float posX = simonNx > 0 ? cr - ZOMBIE_BBOX_WIDTH + 5 : cl + 5; // +-5 to make sure enemy do not out of viewport
				Zombie* zombie = new Zombie({ posX, st - 20 }, -simonNx, ID_SMALL_HEART);
				nonGridObject->push_back(zombie);
			}
		}
	}
}

void ZombieZone::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}
