#include "ZombieZone.h"


ZombieZone::ZombieZone(D3DXVECTOR2 position, int width, int height)
{
	this->x = position.x;
	this->y = position.y;
	this->width = width;
	this->height = height;

	id = ID_ZOMBIE_ZONE;

	spawStart = 0;
	delayTime = 0;
	currentNumZombie = 0;
}

ZombieZone::~ZombieZone()
{
}

void ZombieZone::Update(DWORD dt, vector<LPGAMEOBJECT> *nonGridObject, set<LPGAMEOBJECT> gridObject)
{
	if (spawStart > 0 && GetTickCount() - spawStart > SPAWN_TIME) {
		currentNumZombie = 0;
		spawStart = 0;
	}

	float sl, st, sr, sb, l, t, r, b;
	Simon::GetInstance()->GetBoundingBox(sl, st, sr, sb);
	GetBoundingBox(l, t, r, b);
	int simonNx = Simon::GetInstance()->GetNx();

	CGame* camPosition = CGame::GetInstance();


	numOfZombie = 3;

	if (CGame::GetInstance()->IsColliding({ long(sl),long(st),long(sr),long(sb) },
		{ long(l), long(t), long(r), long(b) }))
	{
		//DebugOut(L"-------Simon is in zombie zone\n");
		if (spawStart == 0 || currentNumZombie < 3) {
			spawStart = GetTickCount();

			
				if (delayTime > 0 && GetTickCount() - delayTime > 800)
					delayTime = 0;

			for (int i = 0; i < numOfZombie; i++) {
				int cl = camPosition->GetCamPosX();
				int ct = camPosition->GetCamPosY();
				int cr = cl + SCREEN_WIDTH;
				int cb = ct + SCREEN_HEIGHT;

				float posX = simonNx > 0 ? cr - ZOMBIE_BBOX_WIDTH + 5 : cl + 5; // +-5 to make sure enemy do not out of viewport
				if (delayTime == 0) {
					DebugOut(L"------Generate zombie\n");
					delayTime = GetTickCount();
					Zombie* zombie = new Zombie({ posX, st - 20 }, -simonNx, ID_SMALL_HEART);
					nonGridObject->push_back(zombie);
					currentNumZombie += 1;
				}
			}
			DebugOut(L"-----current num of zombie: %d\n", currentNumZombie);

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
