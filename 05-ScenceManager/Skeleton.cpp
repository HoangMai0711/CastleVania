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

	attackStart = 1;
	jumpStart = 0;
	spawnBoneStart = 0; 
	numOfBone = 0;

	state = ENEMY_STATE_HIDDEN;

	id = ID_SKELETON;
	score = 200;

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
	if (hitEffectStart > 0)
		ani = ENEMY_ANI_HITTED;
	animations[ani]->Render(x, y);

	if (attackStart > 0)
		for (auto i : weapon) {
			i->Render();
		}
}

void Skeleton::Update(DWORD dt, vector<LPGAMEOBJECT> *nonGridObject, set<LPGAMEOBJECT> gridObject)
{
	if (state == ENEMY_STATE_HIDDEN) {
		//Don't update skeleton're out off screen
		float al, at, ar, ab;
		float bl, bt, br, bb;

		al = CGame::GetInstance()->GetCamPosX();
		at = CGame::GetInstance()->GetCamPosY();

		ar = al + SCREEN_WIDTH;
		ab = at + SCREEN_HEIGHT;

		GetBoundingBox(bl, bt, br, bb);

		RECT A, B;
		A = { long(al),long(at),long(ar),long(ab) };
		B = { long(bl),long(bt),long(br),long(bb) };

		if (!CGame::GetInstance()->IsColliding(A, B))
			return;
	}

	Attack();
	UpdateWeapon(dt, nonGridObject, gridObject);

	CGameObject::Update(dt, nonGridObject, gridObject);

	vy += SKELETON_GRAVITY * dt;

	SetMovingSpace();

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

						if (b < wall->GetY()) {
							if (l < wall->GetX() - 5) {
								isOnGround = false;
								isJump = true;
								jumpStart = GetTickCount();
								vy = -SKELETON_SPEED_Y;
								y -= 5;

								SetMovingSpace();
								MoveToSimon();
							}
							if (r > edge) {
								isOnGround = false;
								isJump = true;
								jumpStart = GetTickCount();
								vy = -SKELETON_SPEED_Y;
								y -= 5;

								SetMovingSpace();
								MoveToSimon();
							}
						}
						else {
							SetMovingSpace();
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

	Simon* simon = Simon::GetInstance();

	float sl, st, sr, sb;
	float l, t, r, b;

	simon->GetBoundingBox(sl, st, sr, sb);
	GetBoundingBox(l, t, r, b);

	if (isFirstActive) {
		if (abs(l - sl) < SKELETON_ACTIVE_DISTANCE_WIDTH && abs(t - st) < SKELETON_ACTIVE_DISTANCE_HEIGHT) {
			isActive = true;
			isFirstActive = false;
			state = ENEMY_STATE_ACTIVE;

			if (jumpStart > 0)
				return;

			MoveToSimon();

		}
	}
	if (!isFirstActive && isActive) {
		if (jumpStart > 0)
			return;
		MoveToSimon();
	}

	if (!(state == ENEMY_STATE_HIDDEN)) {
		DeleteSkeleton();
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

void Skeleton::SetMovingSpace()
{
	Simon* simon = Simon::GetInstance();

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
}

void Skeleton::DeleteSkeleton()
{
	//Delete when out off screen
	float al, at, ar, ab;
	float bl, bt, br, bb;

	float x = CGame::GetInstance()->GetCamPosX();
	float y = CGame::GetInstance()->GetCamPosY();

	al = x;
	at = y;
	ar = x + SCREEN_WIDTH;
	ab = y + SCREEN_HEIGHT;

	GetBoundingBox(bl, bt, br, bb);

	RECT A, B;
	A = { long(al),long(at),long(ar),long(ab) };
	B = { long(bl),long(bt),long(br),long(bb) };

	if (!CGame::GetInstance()->IsColliding(A, B)) {
		state = STATE_DESTROYED;
	}
}

void Skeleton::Antique()
{
	float al, at, ar, ab;
	float bl, bt, br, bb;

	al = CGame::GetInstance()->GetCamPosX();
	at = CGame::GetInstance()->GetCamPosY();

	ar = al + SCREEN_WIDTH;
	ab = at + SCREEN_HEIGHT;

	GetBoundingBox(bl, bt, br, bb);

	RECT A, B;
	A = { long(al),long(at),long(ar),long(ab) };
	B = { long(bl),long(bt),long(br),long(bb) };

	if (!CGame::GetInstance()->IsColliding(A, B))
		return;
}

void Skeleton::Attack()
{
	//DebugOut(L"-----Num of bone: %d\n", numOfBone);
	if (state == ENEMY_STATE_HIDDEN || weapon.size() > 3/* || attackStart > 0*/) {
		return;
	}

	D3DXVECTOR2 skeletonPos = { x, y };

	if (numOfBone == 0 && attackStart>0 && GetTickCount() - attackStart > SKELETON_TIME_ATTACK) {
		attackStart = GetTickCount();
		DebugOut(L"-------Restart attack\n");
		//DebugOut(L"----Num of bone: %d\n", numOfBone);

		numOfBone = rand() % 3 + 1;

		if (attackStart > 0) {
			//DebugOut(L"-------Attack != 0\n");
			return;
		}
	}

	//DebugOut(L"-----Num of bone: %d\n", numOfBone);

	if (spawnBoneStart == 0 && numOfBone > 0) {

		DebugOut(L"----Num of bone: %d\n", numOfBone);
		spawnBoneStart = GetTickCount();

		Bone* bone = new Bone(skeletonPos, nx);
		weapon.push_back(bone);

		numOfBone--;
	}

	if (spawnBoneStart > 0 && GetTickCount() - spawnBoneStart > SPAWN_BONE_TIME)
		spawnBoneStart = 0;

	//isAttack = true;
}

void Skeleton::UpdateWeapon(DWORD dt, vector<LPGAMEOBJECT>* nonGridObject, set<LPGAMEOBJECT> gridObject)
{
	//delete bone
	for (int i = 0; i < weapon.size(); i++)
		if (weapon[i]->GetState() == STATE_DESTROYED)
		{
			weapon.erase(weapon.begin() + i);
			i--;
		}

	for (auto i : weapon)
		i->Update(dt, nonGridObject, gridObject);
}