#pragma once

#include "Game.h"
#include "GameObject.h"
#include "define.h"
#include "TransparentObjects.h"
#include "Utils.h"
#include "Whip.h"
//#include "Wall.h"
#include "Portal.h"
#include "Torch.h"
#include "Weapon.h"
#include "Dagger.h"
#include "Portal.h"
//#include "MoneyBag.h"
#include "HiddenObject.h"
#include "Stair.h"
#include "MovingBrick.h"
#include "Boomerang.h"
#include "Axe.h"
#include "Brick.h"
#include "ActiveBox.h"

#define MARIO_JUMP_DEFLECT_SPEED 0.2f
#define SIMON_DIE_DEFLECT_SPEED	 0.5f
#define SIMON_MAX_HEALTH		16

//Simon velocity
#define SIMON_WALKING_SPEED		0.07f
#define SIMON_JUMP_SPEED_Y		0.21f
#define SIMON_ON_STAIR_SPEED	0.027f
#define SIMON_GRAVITY			0.0006f
#define SIMON_FLASH_TIME		900
#define SIMON_ATTACK_TIME		300
#define SIMON_DIE_TIME			2000
#define SIMON_INJURED_DEFLECT_SPEED_Y	0.15f
#define SIMON_INJURED_DEFLECT_SPEED_X	0.06f

#define SIMON_UNTOUCHABLE_TIME		2000

#define SIMON_STATE_IDLE				0
#define SIMON_STATE_WALKING_RIGHT		1
#define SIMON_STATE_WALKING_LEFT		2
#define SIMON_STATE_JUMP				3
#define SIMON_STATE_DIE					4
#define SIMON_STATE_SIT					5
#define SIMON_STATE_ATTACK				6
#define SIMON_STATE_SIT_ATTACK			7
#define SIMON_STATE_ATTACK_SUBWEAPON	8
#define SIMON_STATE_UPSTAIR				9
#define SIMON_STATE_DOWNSTAIR			10
#define SIMON_STATE_ATTACK_ON_STAIR		11
#define SIMON_STATE_INJURED				12
#define SIMON_STATE_FLASH				13

#define SIMON_ANI_IDLE_RIGHT					0
#define SIMON_ANI_IDLE_LEFT						1
#define SIMON_ANI_WALK_RIGHT					2
#define SIMON_ANI_WALK_LEFT						3
#define SIMON_ANI_ATTACK_RIGHT					4
#define SIMON_ANI_ATTACK_LEFT					5
#define SIMON_ANI_SIT_RIGHT						6
#define SIMON_ANI_SIT_LEFT						7
#define SIMON_ANI_SIT_ATTACK_RIGHT				8
#define SIMON_ANI_SIT_ATTACK_LEFT				9
#define SIMON_ANI_DIE							10
#define SIMON_ANI_IDLE_UPSTAIR_RIGHT			11
#define SIMON_ANI_IDLE_UPSTAIR_LEFT				12
#define SIMON_ANI_IDLE_DOWNSTAIR_RIGHT			13
#define SIMON_ANI_IDLE_DOWNSTAIR_LEFT			14
#define SIMON_ANI_WALK_UPSTAIR_RIGHT			15
#define SIMON_ANI_WALK_UPSTAIR_LEFT				16
#define SIMON_ANI_WALK_DOWNSTAIR_RIGHT			17
#define SIMON_ANI_WALK_DOWNSTAIR_LEFT			18
#define SIMON_ANI_ATTACK_UPSTAIR_RIGHT			19
#define SIMON_ANI_ATTACK_UPSTAIR_LEFT			20
#define SIMON_ANI_ATTACK_DOWNSTAIR_RIGHT		21
#define SIMON_ANI_ATTACK_DOWNSTAIR_LEFT			22
#define SIMON_ANI_INJURED_RIGHT					23
#define SIMON_ANI_INJURED_LEFT					24
#define SIMON_ANI_FLASH_RIGHT					25
#define SIMON_ANI_FLASH_LEFT					26

class Simon: public CGameObject
{
private:
	Simon();

	static Simon* __instance;

	int time;
	int heart;
	int health;
	int life;

	bool isOnAir;
	bool isOnStair;
	bool activatedWall;
	int untouchable;

	DWORD untouchableStart;
	DWORD attackStart;
	DWORD attackSubWeaponStart;
	DWORD flashStart;
	DWORD dieStart;

	bool disableControl;
	int idSubWeapon;

	Whip* whip;
	vector<LPWEAPON> subWeapon;
	int subweaponId;
	int subweaponLevel;

	Stair* stair;
	Stair* collidedStair;

	D3DXVECTOR2 firstPos;
public:
	~Simon();

	static Simon* GetInstance();
	void Load();
	void Unload();
	void Jump();
	void Attack();
	void AttackSubWeapon();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *nonGridObject, set<LPGAMEOBJECT> gridObject);
	virtual void Render();
	void SetState(int state);
	void StartUntouchable() { untouchable = 1; untouchableStart = GetTickCount(); }

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);

	bool IsOnAir() { return isOnAir; }
	bool IsOnStair() { return isOnStair; }
	DWORD GetTimeStartAttack() { return attackStart; }
	bool GetDisableControl() { return disableControl; }
	bool GetActivatedWall() { return activatedWall; }

	void UpdateWhip(DWORD dt, vector<LPGAMEOBJECT> *nonGridObject, set<LPGAMEOBJECT> gridObject);
	void UpdateSubWeapon(DWORD dt, vector<LPGAMEOBJECT> *nonGridObject, set<LPGAMEOBJECT> gridObject);
	void UpgradeWhip();

	void DisableControl() { disableControl = true; }
	void EnableControl() { disableControl = false; }

	void AddSubWeapon(int subWeapon) { this->idSubWeapon = subWeapon; }
	void UnloadWhip();

	void CollideWithObjectAndItems(LPGAMEOBJECT object, vector<LPGAMEOBJECT>* listObject);

	Stair* GetStair() { return stair; }
	Stair* GetCollidedStair() { return collidedStair; }
	void SetStair(Stair* setStair) { stair = setStair; }

	vector<LPWEAPON> GetSubweapon() { return subWeapon; }

	void BeInjured();

	int GetMultiShotLevel() { return subweaponLevel; }
	int GetSubweaponId() { return subweaponId; }
	int GetScore() { return score; }
	int GetTime() { return time; }
	int GetHeart() { return heart; }
	int GetHealth() { return health; }
	int GetLife() { return life; }

	void SetSubweaponLevel(int level) { subweaponLevel = level; }
	void SetSubweaponId(int id) { subweaponId = id; }
	void SetFisrtPosition(float x, float y) { firstPos.x = x; firstPos.y = y; }
	void SetNx(int simonNx) { this->nx = simonNx; }

	void IncreaseHealth(int num);
	void IncreaseHeart(int num);

	void Revive(vector<LPGAMEOBJECT> *nonGridObject);
};

