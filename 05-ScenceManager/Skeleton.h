#pragma once

#include "Enemy.h"
#include "Wall.h"
#include "Bone.h"

#define SKELETON_BBOX_WIDTH			16
#define SKELETON_BBOX_HEIGHT		32

#define SKELETON_ACTIVE_DISTANCE_WIDTH		100
#define SKELETON_ACTIVE_DISTANCE_HEIGHT		60

#define SKELETON_KEEP_SIMON_DISTANCE		51
#define SKELETON_MOVING_SPACE				32

#define SKELETON_GRAVITY		0.0006f
#define SKELETON_SPEED_X		0.075f
#define SKELETON_SPEED_Y		0.21f
#define SKELETON_JUMP_SPEED_X	0.08f

#define SKELETON_STATE_HIDDEN		4

#define SKELETON_ANI_IDLE_RIGHT			1
#define SKELETON_ANI_IDLE_LEFT			2
#define SKELETON_ANI_WALKING_RIGHT		3
#define SKELETON_ANI_WALKING_LEFT		4
#define SKELETON_ANI_HIDDEN				5

#define SKELETON_TIME_ATTACK		3000
#define SKELETON_TIME_JUMP			300
#define SPAWN_BONE_TIME				400

class Skeleton :
	public Enemy
{
	bool isActive;
	bool isFirstActive;
	bool isJump;
	bool isAttack;
	bool isOnGround;

	float leftBlock;
	float rightBlock;

	DWORD attackStart;
	DWORD jumpStart;
	DWORD spawnBoneStart;

	vector<Bone*> weapon;
	int numOfBone;
public:
	Skeleton(D3DXVECTOR2 position);
	~Skeleton();

	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *nonGridObject, set<LPGAMEOBJECT> gridObject);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	void MoveToSimon();
	void SetMovingSpace();
	void DeleteSkeleton();
	void Antique();

	void Attack();
	void UpdateWeapon(DWORD dt, vector<LPGAMEOBJECT> *nonGridObject, set<LPGAMEOBJECT> gridObject);
};

