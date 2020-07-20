#include "Skeleton.h"



Skeleton::Skeleton(D3DXVECTOR2 position)
{
	this->x = position.x;
	this->y = position.y;
	//this->nx = -Simon::GetInstance()->GetNx();
	vx = vy = 0;
	isActive = false;
	isFirstActive = true;
	isJump = false;
	isAttack = false;
	isOnGround = true;

	attackStart = 0;
	jumpStart = 0;

	state = ENEMY_STATE_HIDDEN;

	id = ID_SKELETON;

	AddAnimation(ID_ANI_SKELETON_IDLE_RIGHT);
	AddAnimation(ID_ANI_SKELETON_WALKING_RIGHT);
	AddAnimation(ID_ANI_SKELETON_WALKING_LEFT);
	AddAnimation(ID_ANI_SKELETON_IDLE_LEFT);
}

Skeleton::~Skeleton()
{
}

void Skeleton::Render()
{

	int ani = 0;
	switch (state)
	{
	case ENEMY_STATE_DIE:
		ani = ENEMY_ANI_HITTED;
		break;
	case ENEMY_STATE_IDLE:
		if (nx > 0)
			ani = SKELETON_ANI_IDLE_RIGHT;
		else
			ani = SKELETON_ANI_IDLE_LEFT;
		break;
	case ENEMY_STATE_ACTIVE:
		if (nx > 0)
			ani = SKELETON_ANI_WALKING_RIGHT;
		else
			ani = SKELETON_ANI_WALKING_LEFT;
		break;
	case ENEMY_STATE_HIDDEN:
		ani = ENEMY_ANI_HIDDEN;
		break;
	default:
		break;
	}
	animations[ani]->Render(x, y);
}

void Skeleton::Update(DWORD dt, vector<LPGAMEOBJECT> *nonGridObject, set<LPGAMEOBJECT> gridObject)
{
	CGameObject::Update(dt, nonGridObject, gridObject);

	vy += SKELETON_GRAVITY * dt;

	Simon* simon = Simon::GetInstance();

	vector<LPGAMEOBJECT> *realCoObjects;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	realCoObjects = new vector<LPGAMEOBJECT>;

	for (auto i : gridObject) {
		switch (i->GetId())
		{
		case ID_WALL:
			realCoObjects->push_back(i);
			break;
		default:
			break;
		}
	}

	// turn off collision when die 
	CalcPotentialCollisions(realCoObjects, coEvents);

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		x += dx;

		if (nx != 0) {
			vx = 0;
		}
		if (ny < 0) {
			y += min_ty * dy + ny * 0.1f;
			vy = 0;
			isOnGround = true;
		}
		else {
			y += dy;
		}

		if (isOnGround && !isJump)
			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];

				if (dynamic_cast<Wall *>(e->obj)) {
					if (isActive) {
						Wall *wall = dynamic_cast<Wall *>(e->obj);

						float l, t, r, b;
						GetBoundingBox(l, t, r, b);

						float edge = wall->GetX() + wall->GetLength();
						if (l < wall->GetX() - 5) {
							isOnGround = false;
							isJump = true;
							jumpStart = GetTickCount();
							vy = -SKELETON_SPEED_Y;
							y -= 5;
							MoveToSimon();
						}
						if (r > edge) {
							isOnGround = false;
							isJump = true;
							jumpStart = GetTickCount();
							vy = -SKELETON_SPEED_Y;
							y -= 5;
							MoveToSimon();
						}
					}
				}
			}

		if (jumpStart > 0 && GetTickCount() - jumpStart > SKELETON_TIME_JUMP) {
			isJump = false;
			jumpStart = 0;
		}
	}

	UpdateWeapon(dt, nonGridObject, gridObject);

	float sl, st, sr, sb;
	float l, t, r, b;

	simon->GetBoundingBox(sl, st, sr, sb);
	GetBoundingBox(l, t, r, b);

	if (x < simon->GetX()) {
		nx = 1;
		leftBlock = simon->GetX() - SKELETON_KEEP_SIMON_DISTANCE - SKELETON_MOVING_SPACE;
		rightBlock = leftBlock + SKELETON_MOVING_SPACE;
	}
	else {
		nx = -1;
		leftBlock = simon->GetX() + SKELETON_KEEP_SIMON_DISTANCE;
		rightBlock = leftBlock + SKELETON_MOVING_SPACE;
	}

	if (isFirstActive) {
		if (abs(l - sl) < SKELETON_ACTIVE_DISTANCE_WIDTH && abs(t - st) < SKELETON_ACTIVE_DISTANCE_HEIGHT) {
			isActive = true;
			isFirstActive = false;
			state = ENEMY_STATE_ACTIVE;

			if (jumpStart > 0)
				return;

			MoveToSimon();

			Attack(dt, nonGridObject, gridObject);

		}
	}
	if (!isFirstActive && isActive) {
		if (jumpStart > 0)
			return;
		MoveToSimon();

		if (!isAttack)
		{
			Attack(dt, nonGridObject, gridObject);
		}
	}
}

void Skeleton::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + SKELETON_BBOX_WIDTH;
	bottom = y + SKELETON_BBOX_HEIGHT;
}

void Skeleton::MoveToSimon()
{
	Simon* simon = Simon::GetInstance();

	float sl, st, sr, sb;
	float l, t, r, b;

	simon->GetBoundingBox(sl, st, sr, sb);
	GetBoundingBox(l, t, r, b);

	if (x < leftBlock)
		vx = SKELETON_SPEED_X;
	if (x > rightBlock)
		vx = -SKELETON_SPEED_X;


	if (nx > 0)
		if ((abs(l - sl) < SKELETON_KEEP_SIMON_DISTANCE)) {
			vx = -SKELETON_SPEED_X;
		}
	if (nx < 0)
		if ((abs(l - sl) < SKELETON_KEEP_SIMON_DISTANCE)) {
			vx = SKELETON_SPEED_X;
		}
}

void Skeleton::Attack(DWORD dt, vector<LPGAMEOBJECT> *nonGridObject, set<LPGAMEOBJECT> gridObject)
{
	//DebugOut(L"-------Skeleton attack\n");
	attackStart = GetTickCount();

	D3DXVECTOR2 skeletonPos;
	GetPosition(skeletonPos.x, skeletonPos.y);

	int numOfBone = rand() % 3 + 1;

	for (int i = 0; i < numOfBone; i++) {
		Bone* bone = new Bone(skeletonPos, nx);
		weapon.push_back(bone);
	}
}

void Skeleton::UpdateWeapon(DWORD dt, vector<LPGAMEOBJECT>* nonGridObject, set<LPGAMEOBJECT> gridObject)
{
	if (attackStart > 0 && GetTickCount() - attackStart > SKELETON_TIME_ATTACK) {
		attackStart = 0;
		isAttack = false;
	}

	for (auto i : weapon)
		i->Update(dt, nonGridObject, gridObject);
}
