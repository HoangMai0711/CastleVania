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
public: 
	CSprite(int id, int left, int top, int right, int bottom, int idTexture, int isFlippedHorizontally);

	void Draw(float x, float y, int alpha = 255);
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
	void Add(int id, int left, int top, int right, int bottom, int idTexture, int isFlippedHorizontally);
	LPSPRITE Get(int id);
	void CSprites::Clear();

	static CSprites * GetInstance();
};



