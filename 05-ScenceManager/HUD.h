#define _CRT_NONSTDC_NO_DEPRECATE
#pragma once

#include "Utils.h"
#include "Game.h"
#include "Textures.h"
#include "Text.h"
#include "Simon.h"
#include "Sprites.h"
#include "define.h"

class HUD
{
	static HUD* __instance;

	LPDIRECT3DTEXTURE9 texBackground;
	LPDIRECT3DTEXTURE9 texHealth;
	unordered_map<int, RECT>* listHealth;

	LPTEXT text;

	Simon* player;
	int enemyHealth;

	HUD();
	void DrawHealth(int id, D3DXVECTOR2 position);

	LPSPRITE GetItemSprite();
	LPSPRITE GetMultiShootSprite();

public:
	~HUD();

	void Draw(D3DXVECTOR2 position);
	static HUD* GetInstance();
	void Render();
	void Load();

	void SetEnemyHealth(int health);
};

typedef HUD* LPHUD;
