#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>
#include "Textures.h"

using namespace std;

class CSprite
{
	int id;				// Sprite ID in the sprite database

	int left; 
	int top;
	int right;
	int bottom;
	int isFlippedHorizontally;

	LPDIRECT3DTEXTURE9 texture;

	D3DXVECTOR2 position;
public: 
	CSprite(int id, int left, int top, int right, int bottom, int idTexture, int isFlippedHorizontally, D3DXVECTOR2 position);

	void Draw(float x, float y, int alpha = 255, bool isHUD=0);

	//Get sprites position
	D3DXVECTOR2 GetPosition() { return this->position; }
	int GetSpriteId() { return id; }
};

typedef CSprite * LPSPRITE;

/*
	Manage sprite database
*/
class CSprites
{
	static CSprites * __instance;

	unordered_map<int, LPSPRITE> sprites;

public:
	void Add(int id, int left, int top, int right, int bottom, int idTexture, int isFlippedHorizontally, D3DXVECTOR2 position);
	LPSPRITE Get(int id);
	void CSprites::Clear();

	static CSprites * GetInstance();
};



