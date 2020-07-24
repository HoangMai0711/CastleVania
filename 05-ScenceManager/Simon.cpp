#include "Simon.h"


Simon* Simon::__instance;

Simon::Simon()
{
	id = ID_SIMON;
	isOnAir = false;
	isOnGround = false;
	isOnStair = false;
	isJumping = false;
	isFalling = false;

	life = 3;
	//health = SIMON_MAX_HEALTH;
	health = 2;
	time = 300;
	heart = 5;
	score = 0;

	attackStart = 0;
	onmBrickStart = 0;
	attackSubWeaponStart = 0;
	flashStart = 0;
	untouchableStart = 0;
	calculateScoreStart = 0;
	timeStart = GetTickCount();
	lyingStart = 0;
	fallingStart = 0;
	fallSitStart = 0;

	subweaponId = 0;
	subweaponLevel = 1;

	disableControl = false;

	stair = NULL;
	collidedStair = NULL;
	mBrick = NULL;
	colidingWall = NULL;

	whip = new Whip();

	Load();
}


Simon::~Simon()
{
	delete whip;

	for (auto i : subWeapon)
		delete i;
	subWeapon.clear();

	delete __instance;
	__instance = NULL;
	DebugOut(L"--------Instance is NULL: %d", int(__instance == NULL));
}

Simon * Simon::GetInstance()
{
	if (__instance == NULL) __instance = new Simon();
	return __instance;
}

void Simon::Load()
{
	animations.clear();

	AddAnimation(ID_ANI_SIMON_IDLE_RIGHT);				// Idle Right			0
	AddAnimation(ID_ANI_SIMON_IDLE_LEFT);				// Idle Left			1
	AddAnimation(ID_ANI_SIMON_WALK_RIGHT);				// Walk Right			2
	AddAnimation(ID_ANI_SIMON_WALK_LEFT);				// Walk Left			3
	AddAnimation(ID_ANI_SIMON_ATTACK_RIGHT);			// Attack Right			4
	AddAnimation(ID_ANI_SIMON_ATTACK_LEFT);				// Attack Left			5
	AddAnimation(ID_ANI_SIMON_SIT_RIGHT);				// Sit Right			6
	AddAnimation(ID_ANI_SIMON_SIT_LEFT);				// Sit Left				7
	AddAnimation(ID_ANI_SIMON_SIT_ATTACK_RIGHT);		// Sit Attack Right		8
	AddAnimation(ID_ANI_SIMON_SIT_ATTACK_LEFT);			// Sit Attack Left		9
	AddAnimation(ID_ANI_SIMON_DIE);						// Die					10
	AddAnimation(ID_ANI_SIMON_IDLE_UPSTAIR_RIGHT);		// Idle Upstair Right		11
	AddAnimation(ID_ANI_SIMON_IDLE_UPSTAIR_LEFT);		// Idle Upstair Left		12
	AddAnimation(ID_ANI_SIMON_IDLE_DOWNSTAIR_RIGHT);	// Idle Downstair Right		13 
	AddAnimation(ID_ANI_SIMON_IDLE_DOWNSTAIR_LEFT);		// Idle Downstair Left		14
	AddAnimation(ID_ANI_SIMON_WALK_UPSTAIR_RIGHT);		// Walk Upstair Right		15
	AddAnimation(ID_ANI_SIMON_WALK_UPSTAIR_LEFT);		// Walk Upstair Left		16
	AddAnimation(ID_ANI_SIMON_WALK_DOWNSTAIR_RIGHT);	// Walk Downstair Right		17
	AddAnimation(ID_ANI_SIMON_WALK_DOWNSTAIR_LEFT);		// Walk Downstair Left		18
	AddAnimation(ID_ANI_SIMON_ATTACK_UPSTAIR_RIGHT);	// Attack Upstair Right		19
	AddAnimation(ID_ANI_SIMON_ATTACK_UPSTAIR_LEFT);		// Attack Upstair Left		20
	AddAnimation(ID_ANI_SIMON_ATTACK_DOWNSTAIR_RIGHT);	// Attack Downstair Right	21
	AddAnimation(ID_ANI_SIMON_ATTACK_DOWNSTAIR_LEFT);	// Attack Downstair Left	22
	AddAnimation(ID_ANI_SIMON_INJURED_DEFLECT_RIGHT);	// Injured Deflect Right	23
	AddAnimation(ID_ANI_SIMON_INJURED_DEFLECT_LEFT);	// Injured Deflect Left		24
	AddAnimation(ID_ANI_SIMON_FLASH_RIGHT);				// Flash Right				25
	AddAnimation(ID_ANI_SIMON_FLASH_LEFT);				// Flash Left				26

	whip->Load();
	activatedWall = false;
	isOnMovingBrick = false;
}

void Simon::Unload()
{
	__instance == NULL;
}

void Simon::Jump()
{
	SetState(SIMON_STATE_JUMP);
	isOnAir = true;
	isJumping = true;
}

void Simon::Attack()
{
	if (attackStart > 0)
		return;
	if (isFalling || fallSitStart > 0)
		return;

	if (state != SIMON_STATE_JUMP)
		vx = 0;

	ResetAnimation();
	whip->ResetAnimation();

	if (state == SIMON_STATE_SIT)
		SetState(SIMON_STATE_SIT_ATTACK);
	else if (isOnStair)
		SetState(SIMON_STATE_ATTACK_ON_STAIR);
	else {
		SetState(SIMON_STATE_ATTACK);
		//DebugOut(L"[INFO] Changed state to attack\n");
	}

	attackStart = GetTickCount();
}

void Simon::AttackSubWeapon()
{
	if (attackStart > 0)
		return;
	if (attackSubWeaponStart > 0)
		return;
	if (GetSubweapon().size() >= subweaponLevel)
		return;
	if (isFalling || fallSitStart > 0)
		return;

	if (state != SIMON_STATE_JUMP)
		vx = 0;

	ResetAnimation();

	if (state == SIMON_STATE_SIT)
		SetState(SIMON_STATE_SIT_ATTACK);
	else if (isOnStair)
		SetState(SIMON_STATE_ATTACK_ON_STAIR);
	else
		SetState(SIMON_STATE_ATTACK);

	attackSubWeaponStart = GetTickCount();

	D3DXVECTOR2 simonCurrentPosition;
	GetPosition(simonCurrentPosition.x, simonCurrentPosition.y);

	switch (idSubWeapon)
	{
	case ID_DAGGER:
	{
		Dagger* dagger = new Dagger(simonCurrentPosition, nx);
		subWeapon.push_back(dagger);
		break;
	}
	case ID_BOOMERANG:
	{
		Boomerang* boomerang = new Boomerang(simonCurrentPosition, nx);
		subWeapon.push_back(boomerang);
		break;
	}
	case ID_AXE:
	{
		Axe* axe = new Axe(simonCurrentPosition, nx);
		subWeapon.push_back(axe);
		break;
	}
	default:
		break;
	}
}

void Simon::Update(DWORD dt, vector<LPGAMEOBJECT> *nonGridObject, set<LPGAMEOBJECT> gridObject)
{
	//DebugOut(L"----Simon Pos x-y: %f-%f\n", x, y);
	if (GetTickCount() - attackStart > SIMON_ATTACK_TIME)
		attackStart = 0;

	if (GetTickCount() - attackSubWeaponStart > SIMON_ATTACK_TIME)
		attackSubWeaponStart = 0;

	if (calculateScoreStart > 0)
	{
		if (health < SIMON_MAX_HEALTH)
		{
			if (GetTickCount() - calculateScoreStart > 100)
			{
				health++;
				calculateScoreStart = GetTickCount();
			}
		}
		else if (time > 0)
		{
			if (GetTickCount() - calculateScoreStart > 10)
			{
				time--;
				AddScore(10);
				calculateScoreStart = GetTickCount();
			}
		}
		else if (heart > 0)
		{
			if (GetTickCount() - calculateScoreStart > 200)
			{
				heart--;
				AddScore(100);
			}
		}
		else
		{
			//move to next scene
		}
	}
	CGameObject::Update(dt, nonGridObject, gridObject);

	if (!isOnStair)
		vy += SIMON_GRAVITY * dt;

	if (!isJumping && colidingWall && !isOnStair)
	{
		float wl, wt, wr, wb, sl, st, sr, sb;
		colidingWall->GetBoundingBox(wl, wt, wr, wb);
		GetBoundingBox(sl, st, sr, sb);
		if (sr < wl || sl > wr)
		{
			state = SIMON_STATE_IDLE;
			isFalling = true;
			vx = 0;
			vy = SIMON_FALLING_SPEED_Y;
			if (fallingStart == 0)
				fallingStart = GetTickCount();
		}
	}

	vector<LPGAMEOBJECT> *realCoObjects;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	realCoObjects = new vector<LPGAMEOBJECT>;


	for (auto i : gridObject) {
		switch (i->GetId())
		{
		case ID_WALL:
		case ID_PORTAL:
		case ID_BRICK:
		
			realCoObjects->push_back(i);
			break;
		case ID_ONE_WAY_WALL:
			if (activatedWall == true) {
				realCoObjects->push_back(i);
				break;
			}
			else
				break;
		default:
			break;
		}
	}

	for (auto i : *nonGridObject) {
		switch (i->GetId())
		{
		case ID_MOVING_BRICK:
			realCoObjects->push_back(i);
			break;
		default:
			break;
		}
	}

	//// turn off collision when die 
	//if (state != SIMON_STATE_DIE)
	CalcPotentialCollisions(realCoObjects, coEvents);

	if (onmBrickStart > 0 && GetTickCount() - onmBrickStart > 150) {
		mBrick = NULL;
		onmBrickStart = 0;
	}

	for (auto i : coEvents) {
		if (i->obj->GetId() == ID_MOVING_BRICK && onmBrickStart == 0) {
			onmBrickStart = GetTickCount();
			mBrick = dynamic_cast<MovingBrick*>(i->obj);
			dis2mBrick = mBrick->GetX() - x;
		}
	}

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
		LPGAMEOBJECT objectx = NULL, objecty = NULL;

		FilteCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, objectx, objecty);

		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0)
			vx = 0;
		if (ny < 0) {
			vy = 0;
			isOnAir = false;
			if (!isOnGround) isOnGround = true;
			colidingWall = objecty;
			isJumping = false;
			if (isFalling)
			{
				isFalling = false;
				if (GetTickCount() - fallingStart > SIMON_FALL_HIGHT_TIME_START && fallingStart > 0)
				{
					fallSitStart = GetTickCount();
					state = SIMON_STATE_SIT;
				}
				fallingStart = 0;
			}
		}
		else {
			y += dy;
		}


		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CPortal *>(e->obj)) {
				DebugOut(L"------Portal detection\n");
				CPortal *p = dynamic_cast<CPortal *>(e->obj);
				DebugOut(L"Portal: Next scene: %d\n", p->GetSceneId());

				CGame::GetInstance()->SwitchScene(p->GetSceneId());
			}
		}
	}

	if (GetTickCount() - untouchableStart > SIMON_UNTOUCHABLE_TIME && untouchableStart > 0)
		untouchableStart = 0;

	//Collision when attack
	UpdateWhip(dt, nonGridObject, gridObject);

	UpdateSubWeapon(dt, nonGridObject, gridObject);

	for (auto iter : coEvents) delete iter;
	coEvents.clear();

	//collidedStair = NULL;

	vector<LPGAMEOBJECT>* objects;
	objects = new vector<LPGAMEOBJECT>;

	for (auto obj : gridObject)
		objects->push_back(obj);
	for (auto obj : *nonGridObject)
		objects->push_back(obj);


	//turn off collision when die
	if (state != SIMON_STATE_DIE)
		CalcPotentialCollisions(objects, coEvents);

	collidedStair = NULL;
	//Collision with items
	for (auto i : coEvents) {
		LPGAMEOBJECT object = i->obj;

		//Skip if items is destroyed
		CollideWithObjectAndItems(object, objects);
		CollideWithHiddenObject(object, nonGridObject);
	}

	//Enable control after flash time
	if (GetTickCount() - flashStart > SIMON_FLASH_TIME && flashStart > 0) {
		EnableControl();
		flashStart = 0;
	}

	//Clean up SweptAABB collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	coEvents.clear();


	//Check collision if 2 object is already overlapped
	for (auto iter : *objects)
	{
		float al, at, ar, ab;
		float bl, bt, br, bb;
		GetBoundingBox(al, at, ar, ab);
		iter->GetBoundingBox(bl, bt, br, bb);

		RECT A, B;
		A = { long(al),long(at),long(ar),long(ab) };
		B = { long(bl),long(bt),long(br),long(bb) };

		if (CGame::GetInstance()->IsColliding(A, B)) {
			CollideWithObjectAndItems(iter, objects);
			CollideWithHiddenObject(iter, nonGridObject);
		}
	}

	// reset falling sit state
	if (GetTickCount() - fallSitStart > SIMON_FALL_SIT_TIME && fallSitStart > 0)
		fallSitStart = 0;

	if (isOnStair && stair) {
		float sx, sy;
		stair->GetPosition(sx, sy);
		if ((stair->GetNy() > 0 && (y <= sy - stair->GetStairHeight() - SIMON_BBOX_HEIGHT || y >= sy - SIMON_BBOX_HEIGHT + 5)) ||
			(stair->GetNy() < 0 && (y + SIMON_BBOX_HEIGHT <= sy + 4 || y >= sy + stair->GetStairHeight() - SIMON_BBOX_HEIGHT + 5))) {
			isOnStair = false;
			state = SIMON_STATE_IDLE;
			SetSpeed(0, 0);
			//DebugOut(L"---Simon Pos X-Y: %f-%f\n", x, y);
			//DebugOut(L"---Stair POS x-y,NY: %f-%f,%d\n", sx, sy, stair->GetNy());
			stair = NULL;
		}
	}

	if (GetTickCount() - timeStart > 1000)
	{
		if (calculateScoreStart > 0)
			return;
		timeStart = GetTickCount();
		if (time > 0)
			time--;

		//Set Simon die if time is over
		if (time == 0 && state != SIMON_STATE_DIE && calculateScoreStart == 0)
		{
			health = 0;
			state = SIMON_STATE_DIE;
			isOnStair = false;
			DisableControl();
			lyingStart = GetTickCount();
		}
	}

	if (mBrick != NULL)
		DebugOut(L"dis y: %d \n",dis2mBrick);

	if (mBrick != NULL && y + SIMON_BBOX_HEIGHT <= mBrick->GetY() && (state == SIMON_STATE_IDLE || state == SIMON_STATE_ATTACK || state == SIMON_STATE_SIT_ATTACK)) {
		x = mBrick->GetX() - dis2mBrick;
		vx = 0;
	}

	// update die state
	if (GetTickCount() - lyingStart > SIMON_LYING_TIME && lyingStart > 0)
	{
		DebugOut(L"----Lying\n");
		lyingStart = 0;
		if (life > 0)
			Revive(nonGridObject);
		else
		{
			// move to next scene
		}
	}

}

void Simon::Render()
{
	int ani = -1;

	switch (state)
	{
	case SIMON_STATE_DIE:
		ani = SIMON_ANI_DIE;
		break;
	case SIMON_STATE_ATTACK:
		if (nx > 0)
			ani = SIMON_ANI_ATTACK_RIGHT;
		else
			ani = SIMON_ANI_ATTACK_LEFT;
		break;
	case SIMON_STATE_SIT_ATTACK:
		if (nx > 0)
			ani = SIMON_ANI_SIT_ATTACK_RIGHT;
		else
			ani = SIMON_ANI_SIT_ATTACK_LEFT;
		break;
	case SIMON_STATE_ATTACK_ON_STAIR:
		if (nx > 0 && ny > 0)
			ani = SIMON_ANI_ATTACK_UPSTAIR_RIGHT;
		else if (nx < 0 && ny > 0)
			ani = SIMON_ANI_ATTACK_UPSTAIR_LEFT;
		else if (nx > 0 && ny < 0)
			ani = SIMON_ANI_ATTACK_DOWNSTAIR_RIGHT;
		else if (nx < 0 && ny < 0)
			ani = SIMON_ANI_ATTACK_DOWNSTAIR_LEFT;
		break;
	case SIMON_STATE_JUMP:
		if (vy < 0) {
			if (nx > 0)
				ani = SIMON_ANI_SIT_RIGHT;
			else
				ani = SIMON_ANI_SIT_LEFT;
		}
		else
			if (nx > 0)
				ani = SIMON_ANI_IDLE_RIGHT;
			else
				ani = SIMON_ANI_IDLE_LEFT;
	case SIMON_STATE_SIT:
		if (nx > 0)
			ani = SIMON_ANI_SIT_RIGHT;
		else
			ani = SIMON_ANI_SIT_LEFT;
		break;
	case SIMON_STATE_UPSTAIR:
	{

		if (nx > 0)
			ani = SIMON_ANI_WALK_UPSTAIR_RIGHT;
		else
			ani = SIMON_ANI_WALK_UPSTAIR_LEFT;
		break;
	}
	case SIMON_STATE_DOWNSTAIR:
	{

		if (nx > 0)
			ani = SIMON_ANI_WALK_DOWNSTAIR_RIGHT;
		else
			ani = SIMON_ANI_WALK_DOWNSTAIR_LEFT;
		break;
	}
	case SIMON_STATE_WALKING_RIGHT:
		ani = SIMON_ANI_WALK_RIGHT;
		break;
	case SIMON_STATE_WALKING_LEFT:
		ani = SIMON_ANI_WALK_LEFT;
		break;
	case SIMON_STATE_INJURED:
		if (nx > 0) {
			//DebugOut(L"----SIMON injured right\n");
			ani = SIMON_ANI_INJURED_RIGHT;
		}
		else {
			//DebugOut(L"----SIMON injured left\n");
			ani = SIMON_ANI_INJURED_LEFT;
		}
		break;
	case SIMON_STATE_FLASH:
		if (nx > 0)
			ani = SIMON_ANI_FLASH_RIGHT;
		else
			ani = SIMON_ANI_FLASH_LEFT;
		break;
	default:
		if (isOnStair && vx == 0 && vy == 0) {
			if (nx > 0 && ny > 0)
				ani = SIMON_ANI_IDLE_UPSTAIR_RIGHT;
			else if (nx < 0 && ny < 0)
				ani = SIMON_ANI_IDLE_DOWNSTAIR_LEFT;
			else if (nx < 0 && ny > 0)
				ani = SIMON_ANI_IDLE_UPSTAIR_LEFT;
			else
				ani = SIMON_ANI_IDLE_DOWNSTAIR_RIGHT;

			break;
		}
		else if (nx > 0)
			ani = SIMON_ANI_IDLE_RIGHT;
		else
			ani = SIMON_ANI_IDLE_LEFT;
		break;
	}

	//DebugOut(L"----Simon state/ ani/ nx/ ny: %d/ %d/ %d/ %d\n", state, ani, nx, ny);

	int alpha = 255;
	if (untouchable)
		alpha = 50;

	if (untouchableStart > 0)
		alpha = rand() % 100 > 50 ? 80 : 170;
	//Render animation
	animations[ani]->Render(x, y, alpha);

	if (attackStart)
		whip->Render();

	for (auto i : subWeapon) {
		i->Render();
	}

	RenderBoundingBox();
}

void Simon::SetState(int state)
{
	//if (isOnAir && (state == SIMON_STATE_ATTACK))
	//	return;
	if (isFalling || fallSitStart > 0)
		return;
	if (attackStart > 0)
		return;
	if (attackSubWeaponStart > 0)
		return;


	CGameObject::SetState(state);
	switch (state)
	{
	case SIMON_STATE_WALKING_RIGHT:
		vx = SIMON_WALKING_SPEED;
		nx = 1;
		break;
	case SIMON_STATE_WALKING_LEFT:
		vx = -SIMON_WALKING_SPEED;
		nx = -1;
		break;
	case SIMON_STATE_JUMP:
		vy = -SIMON_JUMP_SPEED_Y;
		y -= 5;
		break;
	case SIMON_STATE_IDLE:
		vx = 0;
		break;
	case SIMON_STATE_DIE:
		vx = -SIMON_DIE_DEFLECT_SPEED;
		break;
	case SIMON_STATE_ATTACK:
		break;
	case SIMON_STATE_ATTACK_ON_STAIR:
	case SIMON_STATE_SIT:
		SetSpeed(0, 0);
		break;
	case SIMON_STATE_INJURED:
		break;
	case SIMON_STATE_UPSTAIR:
		nx = stair->GetNx();
		ny = 1;
		isOnStair = true;
		SetSpeed(nx * SIMON_ON_STAIR_SPEED, -ny * SIMON_ON_STAIR_SPEED);
		break;
	case SIMON_STATE_DOWNSTAIR:
		nx = -stair->GetNx();
		ny = -1;
		isOnStair = true;
		SetSpeed(nx * SIMON_ON_STAIR_SPEED, -ny * SIMON_ON_STAIR_SPEED);
		break;
	}
}

void Simon::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	switch (state)
	{
	case SIMON_STATE_SIT:
	case SIMON_STATE_SIT_ATTACK:
		left = x;
		top = y + SIMON_BBOX_HEIGHT - SIMON_BBOX_SIT_HEIGHT;
		right = x + SIMON_BBOX_SIT_WIDTH;
		bottom = y + SIMON_BBOX_HEIGHT;
		break;
	default:
		left = x;
		top = y;
		right = x + SIMON_BBOX_WIDTH;
		bottom = y + SIMON_BBOX_HEIGHT;
		break;
	}
}

void Simon::UpdateWhip(DWORD dt, vector<LPGAMEOBJECT> *nonGridObject, set<LPGAMEOBJECT> gridObject)
{
	if (GetTickCount() - attackStart <= SIMON_ATTACK_TIME)
	{
		float playerX, playerY;
		playerY = (state == SIMON_STATE_SIT_ATTACK ? y + SIMON_BBOX_HEIGHT / 4 : y);
		playerX = x - 2 * nx;

		whip->Update(dt, nonGridObject, gridObject, { playerX, playerY }, nx);
	}
	else if (attackStart > 0)
	{
		attackStart = 0;
		state = (state == SIMON_STATE_SIT_ATTACK ? SIMON_STATE_SIT : SIMON_STATE_IDLE);
		whip->ResetAnimation();
	}
}

void Simon::UpdateSubWeapon(DWORD dt, vector<LPGAMEOBJECT> *nonGridObject, set<LPGAMEOBJECT> gridObject)
{
	if (GetTickCount() - attackSubWeaponStart > SIMON_ATTACK_TIME && attackSubWeaponStart > 0) {
		attackSubWeaponStart = 0;
		state = (state == SIMON_STATE_SIT_ATTACK ? SIMON_STATE_SIT : SIMON_STATE_IDLE);
	}

	for (auto i : subWeapon)
		i->Update(dt, nonGridObject, gridObject);


	//delete subweapon
	for (int i = 0; i < subWeapon.size(); i++)
		if (subWeapon[i]->GetState() == STATE_DESTROYED)
		{
			subWeapon.erase(subWeapon.begin() + i);
			i--;
		}
}

void Simon::UpgradeWhip()
{
	whip->Upgrade();
}

void Simon::UnloadWhip()
{
	delete whip;
}

void Simon::CollideWithObjectAndItems(LPGAMEOBJECT object, vector<LPGAMEOBJECT>* listObject)
{
	if (object->GetState() == STATE_DESTROYED || state == SIMON_STATE_DIE)
		return;

	switch (object->GetId())
	{
	case ID_BIG_HEART:
		IncreaseHeart(10);
		object->SetState(STATE_DESTROYED);
		break;
	case ID_SMALL_HEART:
		IncreaseHeart(1);
		object->SetState(STATE_DESTROYED);
		break;
	case ID_POT_ROAST:
		IncreaseHealth(6);
		object->SetState(STATE_DESTROYED);
		break;
	case ID_DAGGER:
		SetSubweaponId(ID_DAGGER);
		AddSubWeapon(ID_DAGGER);
		object->SetState(STATE_DESTROYED);
		break;
	case ID_WHIP_UPGRADE:
		UpgradeWhip();
		object->SetState(STATE_DESTROYED);
		state = SIMON_STATE_FLASH;
		SetSpeed(0, 0);
		DisableControl();
		flashStart = GetTickCount();
		break;
	case ID_ITEM_BOOMERANG:
		SetSubweaponId(ID_BOOMERANG);
		AddSubWeapon(ID_BOOMERANG);
		object->SetState(STATE_DESTROYED);
		break;
	case ID_ITEM_AXE:
		SetSubweaponId(ID_AXE);
		AddSubWeapon(ID_AXE);
		object->SetState(STATE_DESTROYED);
		break;
	case ID_STAIR:
	{
		//DebugOut(L"----------Collide with stair\n");
		if (!isOnStair)
			stair = dynamic_cast<Stair*>(object);
		collidedStair = dynamic_cast<Stair*>(object);
		break;
	}

	case ID_BAT:
	case ID_BLACK_KNIGHT:
	case ID_GHOST:
	case ID_FLEAMAN:
	case ID_RAVEN:
	case ID_PHANTOM_BAT:
	case ID_SKELETON:
	case ID_ZOMBIE:
		if (untouchableStart > 0)
			break;
		BeInjured();
		break;
	case ID_RED_MONEYBAG:
	case ID_BLUE_MONEYBAG:
	case ID_YELLOW_MONEYBAG:
	case ID_BIG_MONEYBAG:
	case ID_CROWN:
	{
		MoneyBag* moneybag = dynamic_cast<MoneyBag*>(object);
		moneybag->StartShowScore();
		AddScore(moneybag->GetScore());
		break;
	}
	case ID_DOUBLE_SHOT:
		SetSubweaponLevel(2);
		object->SetState(STATE_DESTROYED);
		break;
	case ID_TRIPLE_SHOT:
		SetSubweaponLevel(3);
		object->SetState(STATE_DESTROYED);
		break;
	case ID_CRYSTAL_BALL:
		object->SetState(STATE_DESTROYED);
		StartCalculateScore();
		break;
	case ID_ACTIVE_BBOX:
	{
		ActiveBox* box = dynamic_cast<ActiveBox*>(object);
		box->IsCollide();
		activatedWall = true;
		box->SetState(STATE_DESTROYED);
		break;
	}
	case ID_DEADZONE:
		health = 0;
		state = SIMON_STATE_DIE;
		vx = 0;
		lyingStart = GetTickCount();
		if (life > 0)
			Revive(listObject);
		break;
	default:
		break;
	}
}

void Simon::CollideWithHiddenObject(LPGAMEOBJECT object, vector<LPGAMEOBJECT>* nonGridObject)
{
	if (object->GetState() == STATE_DESTROYED)
		return;

	switch (object->GetId())
	{
	case ID_HIDDEN_OBJECTS:
	{
		//DebugOut(L"----Collide with hidden object\n");
		HiddenObject* hiddenObj = dynamic_cast<HiddenObject*>(object);
		hiddenObj->IsCollide(nonGridObject);
		break;
	}
	default:
		break;
	}
}

void Simon::BeInjured()
{
	if (untouchableStart > 0)
		return;

	health -= 2;
	if (health <= 0) {
		health = 0;
		state = SIMON_STATE_DIE;
		isOnStair = false;
		DisableControl();
		lyingStart = GetTickCount();
		return;
	}

	untouchableStart = GetTickCount();

	if (!isOnStair) {
		SetSpeed(-nx * SIMON_INJURED_DEFLECT_SPEED_X, -SIMON_INJURED_DEFLECT_SPEED_Y);
		isOnGround = false;
		state = SIMON_STATE_INJURED;
	}
}

void Simon::IncreaseHealth(int num)
{
	health += num;
	if (health > SIMON_MAX_HEALTH)
		health = SIMON_MAX_HEALTH;
}

void Simon::IncreaseHeart(int num)
{
	heart += num;
}

void Simon::AddScore(int score)
{
	this->score += score;
}

void Simon::StartCalculateScore()
{
	calculateScoreStart = GetTickCount();
}

void Simon::Revive(vector<LPGAMEOBJECT>* nonGridObject)
{
	for (auto i : *nonGridObject)
		//if (i->GetId() == ID_PHANTOM_BAT)
			i->Reset();
	life -= 1;
	time = 300;
	//health = SIMON_MAX_HEALTH;
	health = 2;
	state = SIMON_STATE_IDLE;
	nx = 1;

	if (life == 1) {
		whip->Degrade();
	}

	activatedWall = false;
	SetPosition(firstPos.x, firstPos.y);
	EnableControl();
}
