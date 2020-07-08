#include "ZombieZone.h"


void ZombieZone::SpawnEnemy(vector<LPGAMEOBJECT>* objects)
{
	int simonNx = Simon::GetInstance()->GetNx();
	CGame* camPosition = CGame::GetInstance();

	int cl = camPosition->GetCamPosX();
	int ct = camPosition->GetCamPosY();
	int cr = cl + SCREEN_WIDTH;
	int cb = ct + SCREEN_HEIGHT;

	float posX = simonNx > 0 ? cr - ZOMBIE_BBOX_WIDTH + 5 : cl + 5; // +-5 to make sure enemy do not out of viewport
	Zombie* zombie = new Zombie({ posX, zombiePosY }, -simonNx, ID_SMALL_HEART);
	objects->push_back(zombie);
}

ZombieZone::ZombieZone(D3DXVECTOR2 position, int width, int height, int y)
{
	this->x = position.x;
	this->y = position.y;
	this->width = width;
	this->height = height;
	this->zombiePosY = y;
	this->numOfZombie = NUMBER_OF_ZOMBIE;
	this->zombieId = ID_ZOMBIE;

	this->delayStart = 0;
	this->currentIter = 0;
	this->firstSpawn = true;

	id = ID_ZOMBIE_ZONE;
}

ZombieZone::~ZombieZone()
{
}

void ZombieZone::Update(DWORD dt, vector<LPGAMEOBJECT> *nonGridObject, set<LPGAMEOBJECT> gridObject)
{
	isActive = false;

	float sl, st, sr, sb, l, t, r, b;
	Simon::GetInstance()->GetBoundingBox(sl, st, sr, sb);
	GetBoundingBox(l, t, r, b);

	if (CGame::GetInstance()->IsColliding({ long(sl),long(st),long(sr),long(sb) },
		{ long(l), long(t), long(r), long(b) }))
	{
		isActive = true;
		if (firstSpawn)
		{
			delayStart = GetTickCount() - DELAY_TIME - currentIter * TIME_BORN - 1;
			firstSpawn = false;
		}
		else if (delayStart == 0)
			delayStart = GetTickCount();
	}

	if (GetTickCount() - delayStart > DELAY_TIME + currentIter * TIME_BORN && delayStart > 0)
	{
		if (!isActive)
			delayStart = GetTickCount() - DELAY_TIME - currentIter * TIME_BORN;
		else
		{
			currentIter++;
			if (currentIter == numOfZombie)
			{
				currentIter = 0;
				delayStart = 0;
			}

			int tmp = 0;
			for (auto iter : *nonGridObject)
				if (iter->GetId() == zombieId && iter->GetState() == ENEMY_STATE_ACTIVE)
					tmp++;

			if (tmp < numOfZombie)
				SpawnEnemy(nonGridObject);
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
