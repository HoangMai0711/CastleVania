#include "Bone.h"


Bone::Bone(D3DXVECTOR2 position, int nx)
{
	this->x = position.x;
	this->y = position.y;
	this->nx = nx;
	vx = nx * BONE_SPEED_X;
	vy = -BONE_SPEED_Y;

	id = ID_BONE;

	AddAnimation(ID_ANI_BONE);
}

Bone::~Bone()
{
}

void Bone::Render()
{
	animations[0]->Render(x, y);
}

void Bone::Update(DWORD dt, vector<LPGAMEOBJECT> *nonGridObject, set<LPGAMEOBJECT> gridObject)
{
	CGameObject::Update(dt, nonGridObject, gridObject);
	x += dx;
	y += dy;

	vy += BONE_GRAVITY * dt;

	// Simon's injured when collide with bone
	Simon* simon = Simon::GetInstance();

	float sl, st, sr, sb;
	float l, t, r, b;

	simon->GetBoundingBox(sl, st, sr, sb);
	GetBoundingBox(l, t, r, b);

	RECT S, B;
	S = { long(sl),long(st),long(sr),long(sb) };
	B = { long(l),long(t),long(r),long(b) };

	if (CGame::GetInstance()->IsColliding(S, B)) {
		simon->BeInjured();
	}

	//Delete when out off screen
	float al, at, ar, ab;

	float x = CGame::GetInstance()->GetCamPosX();
	float y = CGame::GetInstance()->GetCamPosY();

	al = x;
	at = y;
	ar = x + SCREEN_WIDTH;
	ab = y + SCREEN_HEIGHT;

	RECT A;
	A = { long(al),long(at),long(ar),long(ab) };

	if (!CGame::GetInstance()->IsColliding(A, B)) {
		state = STATE_DESTROYED;
	}
}

void Bone::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + BONE_BBOX_WIDTH;
	bottom = y + BONE_BBOX_HEIGHT;
}

float Bone::RandomFloat(float a, float b)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}
