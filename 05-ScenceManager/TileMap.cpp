#include "TileMap.h"
#include "Utils.h"


TileMap* TileMap::__instance;

TileAtlas::TileAtlas()
{
}

TileAtlas::~TileAtlas()
{
	listTile.clear();
}

void TileAtlas::LoadTileAtlasFromFile(LPCWSTR filePath)
{
	DebugOut(L"[INFO]Start loading tile atlas from file: %s\n", filePath);
	//Get information from file
	ifstream file(filePath);
	json j = json::parse(file);

	tileWidth = j["tilesets"][0]["tilewidth"].get<int>();
	tileHeight = j["tilesets"][0]["tileheight"].get<int>();
	numOfColumn = j["tilesets"][0]["columns"].get<int>();

	int tileCount = j["tilesets"][0]["tilecount"].get<int>();

	//Calculate number of tile row
	numOfRow = tileCount / numOfColumn;

	//Get file image path to load
	string tileMapPath = "textures\\" + j["/tilesets/0/image"_json_pointer].get<string>();

	LPCWSTR imagePath = ToLPCWSTR(tileMapPath);

	//Add tile to list of Tile Atlas
	for (int i = 0; i < numOfRow; i++)
	{
		for (int j = 0; j < numOfColumn; j++)
		{
			RECT rTileMap = { j*tileWidth, i*tileHeight, (j + 1)*tileWidth, (i + 1)*tileHeight };
			int idTileMap = j + 1 + (i*numOfColumn);
			listTile.insert(pair<int, RECT>(idTileMap, rTileMap));
		}
	}
	DebugOut(L"[INFO]Image path of tile sets: %s\n", imagePath);
	//Add textures

	int idTextures = j["properties"][0]["value"];
	CTextures::GetInstance()->Add(idTextures, imagePath, D3DCOLOR_XRGB(5, 5, 5));
	this->texture = CTextures::GetInstance()->Get(idTextures);

	//Close file
	file.close();
	DebugOut(L"[INFO]Done loading tile atlas\n");
}

void TileAtlas::DrawTileAtlas(int id, D3DXVECTOR2 position, int alpha)
{
	RECT r = listTile[id];
	CGame::GetInstance()->Draw(position.x, position.y, texture, r.left, r.top, r.right, r.bottom, alpha);
}

int TileAtlas::GetTileWidth()
{
	return tileWidth;
}

int TileAtlas::GetTileHeight()
{
	return tileHeight;
}


TileMap::TileMap()
{
	tileAtlas = new TileAtlas();
}


TileMap * TileMap::GetInstance()
{
	if (__instance == NULL) __instance = new TileMap();
	return __instance;
}

TileMap::~TileMap()
{
	for (int i = 0; i < tileRow; i++)
	{
		delete[] tileMap[i];
	}
	delete tileMap;
}

void TileMap::LoadTileMapFromFile(LPCWSTR filePath)
{
	numOfLevel = 0;
	DebugOut(L"[INFO]Start loading tilemap file: %s\n", filePath);
	ifstream file(filePath);
	json j = json::parse(file);

	tileRow = j["/layers/0/height"_json_pointer].get<int>();
	tileColumn = j["/layers/0/width"_json_pointer].get<int>();
	height = j["/height"_json_pointer].get<int>();

	// Load cam limit
	camLimitX = new int*[j["cam_limit"].size()];
	for (auto iter : j["cam_limit"])
	{
		camLimitX[numOfLevel] = new int[2];
		camLimitX[numOfLevel][0] = int(iter[0]);
		camLimitX[numOfLevel][1] = int(iter[1]);
		++numOfLevel;
	}
	//DebugOut(L"[INFO] Num of map level: %d", numOfLevel);

	for (int i = 0; i < numOfLevel; ++i) {
		DebugOut(L"----asdc %d-%d\n", camLimitX[i][0], camLimitX[i][1]);
	}

	vector<int> data = j["/layers/0/data"_json_pointer].get<vector<int>>();

	//Map data from vector to matrix
	tileMap = new int*[tileRow];
	for (int i = 0; i < tileRow; i++)
	{
		tileMap[i] = new int[tileColumn];
		for (int j = 0; j < tileColumn; j++)
		{
			int tmp = i * tileColumn + j;
			tileMap[i][j] = data[tmp];
		}
	}
	tileAtlas->LoadTileAtlasFromFile(filePath);
	DebugOut(L"[INFO]Done loading tilemap file\n");
}

void TileMap::Draw(D3DXVECTOR2 position, int alpha)
{
	//DebugOut(L"[INFO]Start draw tilemap\n");
	CGame* camPosition = CGame::GetInstance();

	int camX = camPosition->GetCamPosX();
	int camY = camPosition->GetCamPosY();

	startPosWidth = camX / tileAtlas->GetTileWidth();
	startPosHeight = camY / tileAtlas->GetTileHeight();

	if (startPosWidth < 0)
		startPosWidth = 0;
	if (startPosHeight < 0)
		startPosHeight = 0;

	endPosWidth = startPosWidth + 272 / tileAtlas->GetTileWidth();
	endPosHeight = startPosHeight + 176 / tileAtlas->GetTileHeight() + 2;

	if (endPosWidth > tileColumn)
		endPosWidth = tileColumn;
	if (endPosHeight > tileRow)
		endPosHeight = tileRow;

	//DebugOut(L"----Pos width: Start-End: %d-%d\n", startPosWidth, endPosWidth);
	//DebugOut(L"----Pos height: Start-End: %d-%d\n", startPosHeight, endPosHeight);

	for (int i = startPosHeight; i < endPosHeight; i++)
	{
		for (int j = startPosWidth; j < endPosWidth; j++)
		{
			D3DXVECTOR2 pos;
			pos.x = position.x + j * tileAtlas->GetTileWidth();
			pos.y = position.y + i * tileAtlas->GetTileHeight();
			/*DebugOut(L"-----pos.x-pos.y: %f-%f\n", pos.x, pos.y);*/
			tileAtlas->DrawTileAtlas(tileMap[i][j], pos, 255);
		}
	}
	//DebugOut(L"[INFO]End draw tilemap\n");
}

int TileMap::GetTileMapWidth()
{
	//DebugOut(L"---Tile map width: %d\n", tileColumn*tileAtlas->GetTileWidth());
	return tileColumn*tileAtlas->GetTileWidth();
}

int TileMap::GetTileMapHeight()
{
	//DebugOut(L"---Tile map height: %f\n", tileRow*tileAtlas->GetTileHeight());
	return tileRow*tileAtlas->GetTileHeight();
}

int TileMap::GetCamLtdMin(int numOfLevel)
{
	//DebugOut(L"[INFO] Cam limited min: %d\n", camLimitX[numOfLevel][0]);
	return camLimitX[numOfLevel][0];
}

int TileMap::GetCamLtdMax(int numOfLevel)
{
	//DebugOut(L"[INFO] Cam limited max: %d\n", camLimitX[numOfLevel][1]);
	return camLimitX[numOfLevel][1];
}

void TileMap::SetCamLtdMin(int numOfLevel, int camMin)
{
	camLimitX[numOfLevel][0] = camMin;
}

void TileMap::SetCamLtdMax(int numOfLevel, int camMax)
{
	camLimitX[numOfLevel][1] = camMax;
}

int TileMap::GetMapMaxLevel()
{
	return numOfLevel;
}
