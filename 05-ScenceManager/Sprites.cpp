#include "Sprites.h"
#include "Game.h"
#include "Utils.h"

CSprite::CSprite(int id, int left, int top, int right, int bottom, int idTexture, int isFlippedHorizontally = 0, D3DXVECTOR2 position = {0,0})
{
	this->id = id;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->texture = CTextures::GetInstance()->Get(idTexture);
	this->isFlippedHorizontally = isFlippedHorizontally;
	this->position.x = position.x;
	this->position.y = position.y;
}

CSprites * CSprites::__instance = NULL;

CSprites *CSprites::GetInstance()
{
	if (__instance == NULL) __instance = new CSprites();
	return __instance;
}

void CSprite::Draw(float x, float y, int alpha)
{
	CGame * game = CGame::GetInstance();
	float newX = x + position.x;
	float newY = y + position.y;

	game->Draw(newX, newY, texture, left, top, right, bottom, alpha, isFlippedHorizontally);
}

void CSprites::Add(int id, int left, int top, int right, int bottom, int idTexture, int isFlippedHorizontally, D3DXVECTOR2 position)
{
	LPSPRITE s = new CSprite(id, left, top, right, bottom, idTexture, isFlippedHorizontally, position);
	sprites[id] = s;

	DebugOut(L"[INFO] sprite added: %d, %d, %d, %d, %d \n", id, left, top, right, bottom);
}

LPSPRITE CSprites::Get(int id)
{
	return sprites[id];
}

/*
	Clear all loaded textures
*/
void CSprites::Clear()
{
	for (auto x : sprites)
	{
		LPSPRITE s = x.second;
		delete s;
	}

	sprites.clear();
}



