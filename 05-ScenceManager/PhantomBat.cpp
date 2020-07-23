#include "PhantomBat.h"



PhantomBat::PhantomBat(D3DXVECTOR2 position)
{
	this->x = position.x;
	this->y = position.y;

	originalX = position.x;
	originalY = position.y;

	idleStart = 0;
	attackStart = 0;
	untouchableStart = 0;
	damagedStart = 0;
	hittedStart = 0;
	deflectStart = 0;
	backStart = 0;
	health = 16;

	id = ID_PHANTOM_BAT;
	state = PHANTOM_BAT_STATE_IDLE;

	AddAnimation(ID_ANI_PHANTOM_BAT_IDLE);
	AddAnimation(ID_ANI_PHANTOM_BAT_ACTIVE);
	AddAnimation(ID_ANI_PHANTOM_BAT_DIE);
	AddAnimation(ID_ANI_PHANTOM_BAT_HITTED);
}

PhantomBat::~PhantomBat()
{
}

void PhantomBat::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + PHANTOM_BAT_BBOX_WIDTH;
	bottom = y + PHANTOM_BAT_BBOX_HEIGHT;
}

void PhantomBat::Update(DWORD dt, vector<LPGAMEOBJECT> *nonGridObject, set<LPGAMEOBJECT> gridObject)
{
	CGameObject::Update(dt, nonGridObject, gridObject);

	if (deflectStart == 0) {
		x += dx;
		y += dy;
	}

	if (state == PHANTOM_BAT_STATE_IDLE) {
		float px, py, sx, sy;
		Simon::GetInstance()->GetPosition(sx, sy);
		GetPosition(px, py);

		if (sx - px > 70) {
			state = PHANTOM_BAT_STATE_ACTIVE;

			backStart = GetTickCount();

			int desX = rand() % (PHANTOM_X_END - PHANTOM_X_START) + PHANTOM_X_START;
			int desY = rand() % (PHANTOM_Y_END - PHANTOM_Y_START) + PHANTOM_Y_START;

			vx = (desX - x) / PHANTOM_BAT_TIME_BACK;
			vy = (desY - y) / PHANTOM_BAT_TIME_BACK;
		}
	}

	if (backStart > 0 && GetTickCount() - backStart > PHANTOM_BAT_TIME_BACK) {
		backStart = 0;
		idleStart = GetTickCount();
	}

	if (idleStart > 0) {
		if (GetTickCount() - idleStart > PHANTOM_TIME_IDLE) {
			idleStart = 0;
			attackStart = GetTickCount();
			float desX, desY;
			Simon::GetInstance()->GetPosition(desX, desY);
			vx = (desX - x) / PHANTOM_BAT_TIME_BACK;
			vy = (desY - y) / PHANTOM_BAT_TIME_BACK;
		}
		else {
			vx = vy = 0;
		}
	}

	if (attackStart > 0 && GetTickCount() - attackStart > PHANTOM_TIME_ATTACK) {
		attackStart = 0;
		backStart = GetTickCount();
		int desX = rand() % (PHANTOM_X_END - PHANTOM_X_START) + PHANTOM_X_START;
		int desY = rand() % (PHANTOM_Y_END - PHANTOM_Y_START) + PHANTOM_Y_START;

		vx = (desX - x) / PHANTOM_BAT_TIME_BACK;
		vy = (desY - y) / PHANTOM_BAT_TIME_BACK;
	}

	if (hittedStart > 0)
		vx = vy = 0;

	if (hittedStart > 0 && GetTickCount() - hittedStart > PHANTOM_BAT_TIME_DIE) {
		state = STATE_DESTROYED;
		hittedStart = 0;

		CrystalBall* cBall = new CrystalBall({ x,y });
		nonGridObject->push_back(cBall);
	}

	if (untouchableStart > 0 && GetTickCount() - untouchableStart > PHANTOM_BAT_TIME_UNTOUCHABLE)
		untouchableStart = 0;
	if (deflectStart > 0 && GetTickCount() - deflectStart > PHANTOM_BAT_TIME_DEFLECT)
		deflectStart = 0;
	if (damagedStart > 0 && GetTickCount() - damagedStart > PHANTOM_BAT_TIME_DAMAGED)
		damagedStart = 0;
}

void PhantomBat::Render()
{
	int ani;
	switch (state)
	{
	case PHANTOM_BAT_STATE_IDLE:
		ani = PHANTOM_BAT_ANI_IDLE;
		break;
	case PHANTOM_BAT_STATE_ACTIVE:
		ani = PHANTOM_BAT_ANI_ACTIVE;
		break;
	case PHANTOM_BAT_STATE_DIE:
		ani = PHANTOM_BAT_ANI_DIE;
	default:
		break;
	}
	animations[ani]->Render(x, y);

	if (damagedStart > 0)
		animations[PHANTOM_BAT_ANI_DAMAGED]->Render(x + PHANTOM_BAT_BBOX_WIDTH / 2, y + PHANTOM_BAT_BBOX_HEIGHT / 2);
}

void PhantomBat::IsHitted()
{
	if (untouchableStart > 0)
		return;

	damagedStart = GetTickCount();
	untouchableStart = GetTickCount();
	deflectStart = GetTickCount();

	health -= 2;
	if (health <= 0)
		health = 0;

	HUD::GetInstance()->SetEnemyHealth(health);

	if (health == 0 && state == PHANTOM_BAT_STATE_ACTIVE) {
		state = PHANTOM_BAT_STATE_DIE;
		hittedStart = GetTickCount();
		SetSpeed(0, 0);
	}
}

void PhantomBat::Reset()
{
	this->x = originalX;
	this->y = originalY;

	idleStart = 0;
	attackStart = 0;
	untouchableStart = 0;
	damagedStart = 0;
	hittedStart = 0;
	deflectStart = 0;
	backStart = 0;
	health = 16;

	id = ID_PHANTOM_BAT;
	state = PHANTOM_BAT_STATE_IDLE;
}
