#include <iostream>
#include <fstream>

#include "PlayScence.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"

using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	key_handler = new CPlayScenceKeyHandler(this);
}

/*
	Load scene resources from scene file (textures, sprites, animations and objects)
	See scene1.txt, scene2.txt for detail format specification
*/

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_TEXTURES 2
#define SCENE_SECTION_SPRITES 3
#define SCENE_SECTION_ANIMATIONS 4
#define SCENE_SECTION_ANIMATION_SETS	5
#define SCENE_SECTION_OBJECTS	6

#define OBJECT_TYPE_MARIO	0
#define OBJECT_TYPE_BRICK	1
#define OBJECT_TYPE_GOOMBA	2
#define OBJECT_TYPE_KOOPAS	3

#define OBJECT_TYPE_PORTAL	50

#define MAX_SCENE_LINE 1024

void CPlayScene::Load()
{
	game = CGame::GetInstance();

	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);

	LoadAnimations();

	tileMap = new TileMap();
	//DebugOut(L"[INFO] Start loading tilemap\n");
	tileMap->LoadTileMapFromFile(sceneFilePath);
	DebugOut(L"[INFO] End loading tilemap\n");

	float simonPosX, simonPosY;

	ifstream f(sceneFilePath);
	json j = json::parse(f);

	for (auto iter : j["layers"])
	{
		if (iter["name"] == "Wall")
			for (auto i : iter["objects"]) {
				int width = i["width"];
				int height = i["height"];
				float x = i["x"];
				float y = i["y"];

				D3DXVECTOR2 position = D3DXVECTOR2({ x,y });

				Wall* wall = new Wall(position, width, height);

				objects.push_back(wall);
				//DebugOut(L"---> Wall W-H-X-Y: %d-%d-%f-%f\n", width, height, x, y);
			}
		else if (iter["name"] == "Torch")
			for (auto i : iter["objects"]) {
				int width = i["width"];
				int height = i["height"];
				float x = i["x"];
				float y = i["y"];
				D3DXVECTOR2 position = D3DXVECTOR2({ x,y });

				int idReward = i["properties"][0]["value"];

				Torch* torch = new Torch(position, idReward);

				objects.push_back(torch);
				//DebugOut(L"--->Torch W-H-X-Y: %d-%d-%f-%f\nNext item:%d\n", width, height, x, y,idReward);
			}
		else if (iter["name"] == "Hidden Objects")
			for (auto i : iter["objects"]) {
				int width = i["width"];
				int height = i["height"];
				float x = i["x"];
				float y = i["y"];
				D3DXVECTOR2 position = D3DXVECTOR2({ x,y });

				int idReward = i["properties"][0]["value"];

				D3DXVECTOR2 rewardPos = D3DXVECTOR2({ i["properties"][1]["value"],i["properties"][2]["value"] });

				HiddenObject* hiddenObj = new HiddenObject(position, idReward, rewardPos);

				objects.push_back(hiddenObj);
				//DebugOut(L"--->Hidden object W-H-X-Y: %d-%d-%f-%f\n", width, height, x, y);
			}
		else if (iter["name"] == "Portal")
			for (auto i : iter["objects"]) {
				int width = i["width"];
				int height = i["height"];
				float x = i["x"];
				float y = i["y"];
				D3DXVECTOR2 position = D3DXVECTOR2({ x,y });

				int nextSceneId = i["properties"][0]["value"];

				CPortal* portal = new CPortal(width, height, position, nextSceneId);

				objects.push_back(portal);
				DebugOut(L"--->Portal W-H-X-Y: %d-%d-%f-%f\nNext scene Id: %d\n", width, height, x, y, nextSceneId);
			}
		else if (iter["name"] == "SimonPos")
			for (auto i : iter["objects"]) {
				simonPosX = float(i["x"]);
				simonPosY = float(i["y"]);
			}
		else if (iter["name"] == "Candle")
			for (auto i : iter["objects"]) {
				int width = i["width"];
				int height = i["height"];
				float x = i["x"];
				float y = i["y"];
				D3DXVECTOR2 position = D3DXVECTOR2({ x,y });

				int idReward = i["properties"][0]["value"];

				Candle* candle = new Candle(position, idReward);

				objects.push_back(candle);
			}
		else if (iter["name"] == "Stair")
			for (auto i : iter["objects"]) {
				int width = i["width"];
				int height = i["height"];
				float x = i["x"];
				float y = i["y"];
				D3DXVECTOR2 position = D3DXVECTOR2({ x,y });

				int stairHeight = i["properties"][0]["value"];
				int nx = i["properties"][1]["value"];
				int ny = i["properties"][2]["value"];

				//DebugOut(L"---Add stair-nx: %s_%d\n", ToLPCWSTR(i["name"]), nx);

				Stair* stair = new Stair(position, stairHeight, width, height, nx, ny);

				objects.push_back(stair);
			}
		else if (iter["name"] == "Bat")
			for (auto i : iter["objects"]) {
				int width = i["width"];
				int height = i["height"];
				float x = i["x"];
				float y = i["y"];
				D3DXVECTOR2 position = D3DXVECTOR2({ x,y });

				int idReward = i["properties"][0]["value"];

				DebugOut(L"-----Add Bat: %s\n", ToLPCWSTR(i["name"]));

				Bat* bat = new Bat(position, width, idReward);

				objects.push_back(bat);
			}
		else if (iter["name"] == "BlackKnight")
			for (auto i : iter["objects"]) {
				int width = i["width"];
				int height = i["height"];
				float x = i["x"];
				float y = i["y"];
				D3DXVECTOR2 position = D3DXVECTOR2({ x,y });

				int edge = i["properties"][0]["value"];
				int nx = i["properties"][1]["value"];
				int idReward = i["properties"][2]["value"];

				BlackKnight* blackKnight = new BlackKnight(position, nx, idReward, edge);

				objects.push_back(blackKnight);
			}
		else if (iter["name"] == "MovingBrick")
			for (auto i : iter["objects"]) {
				int width = i["width"];
				int height = i["height"];
				float x = i["x"];
				float y = i["y"];
				D3DXVECTOR2 position = D3DXVECTOR2({ x,y });

				MovingBrick* movingBrick = new MovingBrick(position);

				objects.push_back(movingBrick);
			}
		else if (iter["name"] == "Ghost")
			for (auto i : iter["objects"]) {
				int width = i["width"];
				int height = i["height"];
				float x = i["x"];
				float y = i["y"];
				D3DXVECTOR2 position = D3DXVECTOR2({ x,y });

				Ghost* ghost = new Ghost(position);

				objects.push_back(ghost);
			}
		else if (iter["name"] == "Fleaman")
			for (auto i : iter["objects"]) {
				int width = i["width"];
				int height = i["height"];
				float x = i["x"];
				float y = i["y"];
				D3DXVECTOR2 position = D3DXVECTOR2({ x,y });

				Fleaman* fleaman = new Fleaman({ x,y });

				objects.push_back(fleaman);
			}
	}

	f.close();
	//DebugOut(L"[INFO] Done loading objects\n");

	simon = Simon::GetInstance();

	simon->SetPosition(simonPosX, simonPosY);

	if (!CGame::GetInstance()->IsFirstLoad())
		simon->Load();

	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	simon->Update(dt, &objects);

	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 1; i < objects.size(); i++)
	{
		if (objects[i]->GetState() == STATE_DESTROYED) {
			objects.erase(objects.begin() + i);
			i--;
		}
		coObjects.push_back(objects[i]);
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &objects);
	}


	// Update camera to follow mario
	float cx, cy;
	simon->GetPosition(cx, cy);

	cx -= game->GetScreenWidth() / 2;
	//cy -= game->GetScreenHeight() / 2;

	// check if camera is out of screen

	float simonPosY = simon->GetY() + SIMON_BBOX_HEIGHT / 2;

	//DebugOut(L"----Tile Map Height: %d\n", tileMap->GetTileMapHeight());
	//DebugOut(L"-----Simon Position Y: %f\n", simonPosY);

	int camFloor = int(simonPosY) / CAM_HEIGHT;
	//DebugOut(L"----cam floor: %d\n", camFloor);

	int maxMapLevel = tileMap->GetMapMaxLevel() - 1;

	camFloor = camFloor > maxMapLevel ? maxMapLevel : camFloor;

	int minWidth = tileMap->GetCamLtdMin(camFloor);
	int maxWidth = tileMap->GetCamLtdMax(camFloor);

	if (cx < minWidth) {
		//DebugOut(L"------cx<0: %f\n", cx);
		cx = minWidth;
	}
	if (cx + game->GetScreenWidth() > maxWidth) {
		cx = maxWidth - game->GetScreenWidth();
	}
	cy = camFloor * CAM_HEIGHT;

	CGame::GetInstance()->SetCamPos(cx, cy);
}

void CPlayScene::Render()
{
	//DebugOut(L"[INFO]Render objects in Playscene\n");
	tileMap->Draw({ 0,0 }, 255);
	for (int i = 0; i < objects.size(); i++) {
		objects[i]->RenderBoundingBox();
		objects[i]->Render();
	}
	simon->Render();
}

/*
	Unload current scene
*/
void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
}

void CPlayScene::LoadAnimations()
{
	CTextures* textures = CTextures::GetInstance();
	CSprites* sprites = CSprites::GetInstance();
	CAnimations* animations = CAnimations::GetInstance();

	textures->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));

	ifstream f("textures\\animation.json");
	json j = json::parse(f);

	DebugOut(L"[INFO] Start loading animations from: animation.json \n");

	animations->Clear();

	for (auto i : j["texture"])
	{
		LPCWSTR filePath = ToLPCWSTR(i[1]);

		textures->Add(i[0], filePath, i[2]);
	}

	for (auto i : j["sprites"])
	{
		sprites->Add(i[0], i[1], i[2], i[3], i[4], i[5], i[6], { i[7],i[8] });
	}

	LPANIMATION ani;

	for (auto i : j["animation"])
	{
		ani = new CAnimation(i[1]);

		for (int iter : i[2])
		{
			ani->Add(iter);
		}

		animations->Add(i[0], ani);
		DebugOut(L"Added animation %d\n", (int)i[0]);
	}
	f.close();

	DebugOut(L"[INFO]Done loading animations\n");
}

void CPlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	CGame *game = CGame::GetInstance();
	Simon* simon = ((CPlayScene*)scence)->simon;

	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	if (simon->GetDisableControl())
		return;

	switch (KeyCode)
	{
	case DIK_X:
		if (simon->GetState() != SIMON_STATE_JUMP && simon->GetState() != SIMON_STATE_ATTACK)
			simon->Jump();
		break;
	case DIK_Z:
		if (game->IsKeyDown(DIK_UP)) {
			simon->AttackSubWeapon();
		}
		else
			simon->Attack();
		break;
	case DIK_C:
		simon->AttackSubWeapon();
		break;
	case DIK_1:
		game->SwitchScene(1);
		break;
	case DIK_2:
		game->SwitchScene(2);
		break;
	case DIK_3:
		game->SwitchScene(3);
		break;
	case DIK_4:
		game->SwitchScene(4);
		break;
	}
}

void CPlayScenceKeyHandler::OnKeyUp(int KeyCode)
{
	CGame *game = CGame::GetInstance();
	Simon* simon = ((CPlayScene*)scence)->simon;

	switch (KeyCode)
	{
	case DIK_RIGHT:
	case DIK_LEFT:
	case DIK_DOWN:
	case DIK_UP:
		if (simon->IsOnStair())
			simon->SetSpeed(0, 0);
		break;
	default:
		break;
	}
}

void CPlayScenceKeyHandler::KeyState(BYTE *states)
{
	CGame *game = CGame::GetInstance();
	Simon* simon = ((CPlayScene*)scence)->simon;

	if (simon->IsOnAir() == true)
		return;

	if (simon->GetTimeStartAttack() > 0)
		return;

	if (simon->GetState() == SIMON_STATE_DIE/* || simon->GetState() == SIMON_STATE_SIT*/)
		return;

	if (simon->GetDisableControl())
		return;

	simon->SetState(SIMON_STATE_IDLE);

	if (game->IsKeyDown(DIK_RIGHT))
		if (simon->IsOnStair())
			if (simon->GetStair()->GetNx() > 0)
				simon->SetState(SIMON_STATE_UPSTAIR);
			else
				simon->SetState(SIMON_STATE_DOWNSTAIR);
		else
			simon->SetState(SIMON_STATE_WALKING_RIGHT);

	if (game->IsKeyDown(DIK_LEFT))
		if (simon->IsOnStair())
			if (simon->GetStair()->GetNx() < 0)
				simon->SetState(SIMON_STATE_UPSTAIR);
			else
				simon->SetState(SIMON_STATE_DOWNSTAIR);
		else
			simon->SetState(SIMON_STATE_WALKING_LEFT);

	if (game->IsKeyDown(DIK_DOWN))
		if (simon->IsOnStair()) {
			simon->SetState(SIMON_STATE_DOWNSTAIR);
		}
		else if (simon->GetCollidedStair()) {
			if (simon->GetCollidedStair()->GetNy() < 0) {
				float x, y;
				simon->GetCollidedStair()->GetPosition(x, y);
				simon->SetStair(simon->GetCollidedStair());
				simon->SetPosition(x, y - SIMON_BBOX_HEIGHT);
				simon->SetState(SIMON_STATE_DOWNSTAIR);
			}
			else
				simon->SetState(SIMON_STATE_SIT);
		}
		else
			simon->SetState(SIMON_STATE_SIT);

	if (game->IsKeyDown(DIK_UP))
		if (simon->IsOnStair()) {
			simon->SetState(SIMON_STATE_UPSTAIR);
		}
		else if (simon->GetCollidedStair()) {
			if (simon->GetCollidedStair()->GetNy() > 0) {
				float x, y;
				simon->GetCollidedStair()->GetPosition(x, y);
				simon->SetStair(simon->GetCollidedStair());
				simon->SetPosition(x, y - SIMON_BBOX_HEIGHT);
				simon->SetState(SIMON_STATE_UPSTAIR);
			}
		}
}