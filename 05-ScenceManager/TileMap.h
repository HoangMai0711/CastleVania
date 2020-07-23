#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
#include "json.hpp" 
#include "Game.h"
#include "GameObject.h"
#include "Sprites.h"
#include "Textures.h"
#include "define.h"
#include "Utils.h"

using json = nlohmann::json;

class TileAtlas
{
	int tileWidth;
	int tileHeight;
	int numOfColumn;
	int numOfRow;

	map<int, RECT> listTile;
	LPDIRECT3DTEXTURE9 texture;
public:
	TileAtlas();
	~TileAtlas();

	void LoadTileAtlasFromFile(LPCWSTR filePath);
	void DrawTileAtlas(int id, D3DXVECTOR2 position, int alpha = 255);

	int GetTileWidth();
	int GetTileHeight();
};

typedef TileAtlas* LPTILEATLAS;

class TileMap
{
	static TileMap* __instance;

	TileMap();

	int tileRow;
	int tileColumn;
	int height;
	int** camLimitX;
	int numOfLevel = 0;

	LPTILEATLAS tileAtlas;
	int** tileMap;

	int startPosWidth, startPosHeight;
	int endPosWidth, endPosHeight;
public:
	static TileMap* GetInstance();

	~TileMap();

	void LoadTileMapFromFile(LPCWSTR filePath);
	void Draw(D3DXVECTOR2 position, int alpha = 255);
	int GetTileMapWidth();
	int GetTileMapHeight();
	int GetMapMaxLevel();

	int GetCamLtdMin(int numOfLevel);
	int GetCamLtdMax(int numOfLevel);

	void SetCamLtdMin(int numOfLevel, int camMin);
	void SetCamLtdMax(int numOfLevel, int camMax);
};

typedef TileMap* LPTILEMAP;
