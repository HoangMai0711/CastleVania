#include "Raven.h"



Raven::Raven(D3DXVECTOR2 position)
{
	this->x = position.x;
	this->y = position.y;
	state = ENEMY_STATE_IDLE;
	vx = vy = 0;
	nx = -1;
	isActive = false;

	id = ID_RAVEN;

	//AddAnimation(ID_ANI_RAVEN_IDLE_RIGHT);
	AddAnimation(ID_ANI_RAVEN_IDLE_LEFT);
	AddAnimation(ID_ANI_RAVEN_FLY_RIGHT);
	AddAnimation(ID_ANI_RAVEN_FLY_LEFT);
}

Raven::~Raven()
{
}

void Raven::Render()
{
	int ani = 0;
	switch (state)
	{
	case ENEMY_STATE_HITTED:
		ani = ENEMY_ANI_HITTED;
		break;
	case ENEMY_STATE_IDLE:
		/*if (nx > 0)
			ani = RAVEN_ANI_IDLE_RIGHT;
		else*/
			ani = RAVEN_ANI_IDLE_LEFT;
		break;
	case ENEMY_STATE_ACTIVE:
		if (nx > 0)
			ani = RAVEN_ANI_FLY_RIGHT;
		else
			ani = RAVEN_ANI_FLY_LEFT;
		break;
	default:
		break;
	}
	animations[ani]->Render(x, y);
}

void Raven::Update(DWORD dt, vector<LPGAMEOBJECT> *nonGridObject, set<LPGAMEOBJECT> gridObject)
{
	CGameObject::Update(dt, nonGridObject, gridObject);
	x += dx;
	y += dy;

	Simon* simon = Simon::GetInstance();

	float sl, st, sr, sb;
	float rl, rt, rr, rb;

	simon->GetBoundingBox(sl, st, sr, sb);
	GetBoundingBox(rl, rt, rr, rb);

	if (x > simon->GetX() && y < simon->GetY()) {
		nx = -1;
		ny = 1;
	}
	else if (x > simon->GetX() && y > simon->GetY()) {
		nx = -1;
		ny = -1;
	}
	else if (x < simon->GetX() && y < simon->GetY()) {
		nx = 1;
		ny = 1;
	}
	else {
		nx = 1;
		ny = -1;
	}


	if (!isActive && state != STATE_DESTROYED) {
		if (abs(rl - sl) < RAVEN_ACTIVE_DISTANCE_WIDTH && abs(rt - st) < RAVEN_ACTIVE_DISTANCE_HEIGHT) {
			state = ENEMY_STATE_ACTIVE;
			idleStart = 0;
			flyStart = GetTickCount();
			float sx, sy;
			sx = rand() % 20 + 10;
			sy = rand() % 20 + 10;
			vx = nx * sx / RAVEN_TIME_FLY;

			if (y == simon->GetY() + 5) {
				vy = 0;
			}
			else
				vy = ny * sy / RAVEN_TIME_FLY;
			isActive = true;
		}
	}

	if (isActive && state != STATE_DESTROYED) {

		if (flyStart > 0 && GetTickCount() - flyStart > RAVEN_TIME_FLY) {
			DebugOut(L"-----Raven idle\n");
			state = ENEMY_STATE_ACTIVE;
			flyStart = 0;
			idleStart = GetTickCount();
			vx = vy = 0;
		}

		if (idleStart > 0 && GetTickCount() - idleStart > RAVEN_TIME_IDLE) {
			state = ENEMY_STATE_ACTIVE;
			idleStart = 0;
			flyStart = GetTickCount();
			float sx, sy;
			sx = rand() % 40 + 10;
			sy = rand() % 70 + 10;
			DebugOut(L"----sx,sy: %f/ %f\n", sx, sy);
			vx = nx * sx / RAVEN_TIME_FLY;

			if (y == simon->GetY() + 5) {
				vy = 0;
			}
			else
				vy = ny * sy / RAVEN_TIME_FLY;
		}
	}

	RECT S, R;
	S = { long(sl), long(st), long(sr), long(sb) };
	R = { long(rl), long(rt), long(rr), long(rb) };

	if (CGame::GetInstance()->IsColliding(R, S)) {
		/*SetSpeed(0, 0);
		hitEffectStart = GetTickCount();
		state = ENEMY_STATE_HITTED;*/
		state = STATE_DESTROYED;
		//IsHitted();
	}
		

	DWORD effectTimeCount = GetTickCount() - hitEffectStart;

	if (effectTimeCount > HIT_EFFECT_TIME && hitEffectStart > 0) {
		hitEffectStart = 0;
		state = STATE_DESTROYED;
	}
}

void Raven::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + RAVEN_BBOX_WIDTH;
	bottom = y + RAVEN_BBOX_HEIGHT;
}

