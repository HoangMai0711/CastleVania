#include "TileMap.h"
#include "Utils.h"

TileAtlas::TileAtlas()
{
}

TileAtlas::~TileAtlas()
{
	listTile.clear();
}

void TileAtlas::LoadTileAtlasFromFile(LPCWSTR filePath)
{
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

	wstring sTmp;
	sTmp = s2ws(tileMapPath);
	LPCWSTR imagePath = sTmp.c_str();

	//Add tile to list of Tile Atlas
	for (int i = 0; i < numOfRow; i++)
	{
		for (int j = 0; i < numOfColumn; j++)
		{
			RECT rTileMap = { j*tileWidth, i*tileHeight, (j + 1)*tileWidth, (i + 1)*tileHeight };
			int idTileMap = j + 1 + (i*numOfColumn);
			listTile.insert(pair<int, RECT>(idTileMap, rTileMap));
		}
	}

	//Add textures
	CTextures::GetInstance()->Add(ID_TEX_TILE_SCENE01, imagePath, D3DCOLOR_XRGB(0, 0, 0));
	this->texture = CTextures::GetInstance()->Get(ID_TEX_TILE_SCENE01);

	//Close file
	file.close();
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
	ifstream file(filePath);
	json j = json::parse(file);

	tileRow = j["/layers/0/height"_json_pointer].get<int>();
	tileColumn = j["/layers/0/width"_json_pointer].get<int>();
	height = j["/height"_json_pointer].get<int>();

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
}

void TileMap::Draw(D3DXVECTOR2 position, int alpha)
{
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
	endPosHeight = startPosHeight + 176 / tileAtlas->GetTileHeight();

	if (endPosWidth > tileColumn)
		endPosWidth = tileColumn;
	if (endPosHeight > tileRow)
		endPosHeight = tileRow;

	for (int i = startPosHeight; i < endPosHeight; i++)
	{
		for (int j = startPosWidth; j < endPosWidth; i++)
		{
			D3DXVECTOR2 pos;
			pos.x = position.x + j * tileAtlas->GetTileWidth();
			pos.y = position.y + j * tileAtlas->GetTileHeight();
			tileAtlas->DrawTileAtlas(tileMap[i][j], pos, alpha);
		}
	}
}

int TileMap::GetTileMapWidth()
{
	return tileAtlas->GetTileWidth();
}

int TileMap::GetTileMapHeight()
{
	return tileAtlas->GetTileHeight();
}
