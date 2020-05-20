#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>
#include "Utils.h"

#include "Sprites.h"

/*
Sprite animation
*/
class CAnimationFrame
{
	LPSPRITE sprite;
	DWORD time;
	D3DXVECTOR2 position;

	int idSprites;
public:
	CAnimationFrame(LPSPRITE sprite, int time) { this->sprite = sprite; this->time = time; this->position = this->sprite->GetPosition(); this->idSprites = this->sprite->GetSpriteId(); }
	DWORD GetTime() { return time; }
	LPSPRITE GetSprite() { return sprite; }

	//Get position of animation frame
	D3DXVECTOR2 GetPosition() { return this->position; }
	int GetSpriteId() { return this->idSprites; }
};

typedef CAnimationFrame *LPANIMATION_FRAME;

class CAnimation
{
	DWORD lastFrameTime;
	int currentFrame;
	int defaultTime;
	vector<LPANIMATION_FRAME> frames;
public:
	CAnimation(int defaultTime = 100) { this->defaultTime = defaultTime; lastFrameTime = -1; currentFrame = -1; }
	void Add(int spriteId, DWORD time = 0);
	void Reset();
	void Render(float x, float y, int alpha = 255);
	
	int GetCurrentFrame() { return currentFrame; }

	//Get position of current animarion frame
	D3DXVECTOR2 GetFramePosition() { return frames[currentFrame]->GetPosition(); }
	int GetFrameId() { return frames[currentFrame]->GetSpriteId(); }
};

typedef CAnimation *LPANIMATION;

class CAnimations
{
	static CAnimations * __instance;

	unordered_map<int, LPANIMATION> animations;

public:
	void Add(int id, LPANIMATION ani);
	LPANIMATION Get(int id);
	void Clear();

	static CAnimations * GetInstance();
};

typedef vector<LPANIMATION> CAnimationSet;

typedef CAnimationSet* LPANIMATION_SET;

/*
	Manage animation set database
*/
class CAnimationSets
{
	static CAnimationSets * __instance;

	unordered_map<int, LPANIMATION_SET> animation_sets;

public:
	CAnimationSets();
	void Add(int id, LPANIMATION_SET ani);
	LPANIMATION_SET Get(unsigned int id);

	static CAnimationSets * GetInstance();
};