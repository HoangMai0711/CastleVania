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

	tileMap = TileMap::GetInstance();

	tileMap->LoadTileMapFromFile(sceneFilePath);
	DebugOut(L"[INFO] End loading tilemap\n");

	int row, col;
	row = tileMap->GetTileMapHeight() / GRID_HEIGHT + 1;
	col = tileMap->GetTileMapWidth() / GRID_WIDTH + 1;

	grid = new Grid(row, col);

	float simonPosX, simonPosY;
	int simonNx;

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

				for (auto k : i["gridPos"]) {
					int col = k["col"];
					int row = k["row"];
					D3DXVECTOR2 gridPos = D3DXVECTOR2({ float(row),float(col) });
					wall->AddGridPositon(gridPos);
				}

				grid->AddObject(wall);
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

				for (auto k : i["gridPos"]) {
					int col = k["col"];
					int row = k["row"];
					D3DXVECTOR2 gridPos = D3DXVECTOR2({ float(row),float(col) });
					torch->AddGridPositon(gridPos);
				}

				grid->AddObject(torch);
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

				HiddenObject* hiddenObj = new HiddenObject(position, idReward, rewardPos, width, height);

				for (auto k : i["gridPos"]) {
					int col = k["col"];
					int row = k["row"];
					D3DXVECTOR2 gridPos = D3DXVECTOR2({ float(row),float(col) });
					hiddenObj->AddGridPositon(gridPos);
				}

				grid->AddObject(hiddenObj);
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
				simonNx = i["properties"][1]["value"];

				CPortal* portal = new CPortal(width, height, position, nextSceneId, simonNx);

				for (auto k : i["gridPos"]) {
					int col = k["col"];
					int row = k["row"];
					D3DXVECTOR2 gridPos = D3DXVECTOR2({ float(row),float(col) });
					portal->AddGridPositon(gridPos);
				}

				grid->AddObject(portal);
				//DebugOut(L"--->Portal W-H-X-Y: %d-%d-%f-%f\nNext scene Id: %d\n", width, height, x, y, nextSceneId);
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

				for (auto k : i["gridPos"]) {
					int col = k["col"];
					int row = k["row"];
					D3DXVECTOR2 gridPos = D3DXVECTOR2({ float(row),float(col) });
					candle->AddGridPositon(gridPos);
				}

				grid->AddObject(candle);
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

				for (auto k : i["gridPos"]) {
					int col = k["col"];
					int row = k["row"];
					D3DXVECTOR2 gridPos = D3DXVECTOR2{ float(row),float(col) };
					stair->AddGridPositon(gridPos);
				}
				grid->AddObject(stair);
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

				Bat* bat = new Bat(position, idReward);

				nonGridObject.push_back(bat);
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

				nonGridObject.push_back(blackKnight);
			}
		else if (iter["name"] == "MovingBrick")
			for (auto i : iter["objects"]) {
				int width = i["width"];
				int height = i["height"];
				float x = i["x"];
				float y = i["y"];
				D3DXVECTOR2 position = D3DXVECTOR2({ x,y });

				MovingBrick* movingBrick = new MovingBrick(position);

				nonGridObject.push_back(movingBrick);
			}
		else if (iter["name"] == "Ghost")
			for (auto i : iter["objects"]) {
				int width = i["width"];
				int height = i["height"];
				float x = i["x"];
				float y = i["y"];
				D3DXVECTOR2 position = D3DXVECTOR2({ x,y });

				Ghost* ghost = new Ghost(position);

				nonGridObject.push_back(ghost);
			}
		else if (iter["name"] == "Fleaman")
			for (auto i : iter["objects"]) {
				int width = i["width"];
				int height = i["height"];
				float x = i["x"];
				float y = i["y"];
				D3DXVECTOR2 position = D3DXVECTOR2({ x,y });

				Fleaman* fleaman = new Fleaman({ x,y });

				nonGridObject.push_back(fleaman);
			}
		else if (iter["name"] == "Raven")
			for (auto i : iter["objects"]) {
				int width = i["width"];
				int height = i["height"];
				float x = i["x"];
				float y = i["y"];
				D3DXVECTOR2 position = D3DXVECTOR2({ x,y });

				Raven* raven = new Raven(position);

				nonGridObject.push_back(raven);
			}
		else if (iter["name"] == "ZombieZone")
			for (auto i : iter["objects"]) {
				int width = i["width"];
				int height = i["height"];
				float x = i["x"];
				float y = i["y"];
				D3DXVECTOR2 position = D3DXVECTOR2({ x,y });

				float zombieY = i["properties"][0]["value"];

				ZombieZone* zombieZone = new ZombieZone(position, width, height);

				nonGridObject.push_back(zombieZone);
			}
		else if (iter["name"] == "Skeleton")
			for (auto i : iter["objects"]) {
				int width = i["width"];
				int height = i["height"];
				float x = i["x"];
				float y = i["y"];
				D3DXVECTOR2 position = D3DXVECTOR2({ x,y });

				Skeleton* skeleton = new Skeleton(position);

				nonGridObject.push_back(skeleton);
			}
		else if (iter["name"] == "Boss")
			for (auto i : iter["objects"]) {
				int width = i["width"];
				int height = i["height"];
				float x = i["x"];
				float y = i["y"];
				D3DXVECTOR2 position = D3DXVECTOR2({ x,y });

				PhantomBat* boss = new PhantomBat(position);

				nonGridObject.push_back(boss);
			}
		else if (iter["name"] == "Brick")
			for (auto i : iter["objects"]) {
				int width = i["width"];
				int height = i["height"];
				float x = i["x"];
				float y = i["y"];
				D3DXVECTOR2 position = D3DXVECTOR2({ x,y });

				float idReward = i["properties"][1]["value"];

				int idAni = i["properties"][0]["value"];

				CBrick* brick = new CBrick(position, idReward, idAni);

				for (auto k : i["gridPos"]) {
					int col = k["col"];
					int row = k["row"];
					D3DXVECTOR2 gridPos = D3DXVECTOR2{ float(row),float(col) };
					brick->AddGridPositon(gridPos);
				}
				grid->AddObject(brick);
			}
		else if (iter["name"] == "ActiveBox")
			for (auto i : iter["objects"]) {
				int width = i["width"];
				int height = i["height"];
				float x = i["x"];
				float y = i["y"];
				D3DXVECTOR2 position = D3DXVECTOR2({ x,y });

				ActiveBox* box = new ActiveBox(position);

				for (auto k : i["gridPos"]) {
					int col = k["col"];
					int row = k["row"];
					D3DXVECTOR2 gridPos = D3DXVECTOR2{ float(row),float(col) };
					box->AddGridPositon(gridPos);
				}
				grid->AddObject(box);
			}
		else if (iter["name"] == "1-way Wall")
		for (auto i : iter["objects"]) {
			int width = i["width"];
			int height = i["height"];
			float x = i["x"];
			float y = i["y"];
			D3DXVECTOR2 position = D3DXVECTOR2({ x,y });

			OneWayWall* onewayWall = new OneWayWall(position);

			for (auto k : i["gridPos"]) {
				int col = k["col"];
				int row = k["row"];
				D3DXVECTOR2 gridPos = D3DXVECTOR2{ float(row),float(col) };
				onewayWall->AddGridPositon(gridPos);
			}
			grid->AddObject(onewayWall);
		}
	}

	f.close();
	//DebugOut(L"[INFO] Done loading objects\n");

	simon = Simon::GetInstance();

	simon->SetPosition(simonPosX, simonPosY);
	simon->SetFisrtPosition(simonPosX, simonPosY);

	if (!CGame::GetInstance()->IsFirstLoad())
		simon->Load();

	hud = HUD::GetInstance();
	hud->Load();

	DebugOut(L"[INFO] Done loading scene resources: %s\n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	set<LPGAMEOBJECT> currentGridObjects;

	currentGridObjects = grid->GetCurrentObject();
	//DebugOut(L"--current grid object: %d\n", currentGridObjects.size());
	//DebugOut(L"--non grid object: %d\n", nonGridObject.size());


	// update simon
	simon->Update(dt, &nonGridObject, currentGridObjects);

	// update non grid objects

	for (int i = 0; i < nonGridObject.size(); i++) {
		nonGridObject[i]->Update(dt, &nonGridObject, currentGridObjects);
	}

	grid->Update(dt, &nonGridObject, currentGridObjects);

	// delete destroyed objects
	for (int i = 0; i < nonGridObject.size(); ++i) {
		if (nonGridObject[i]->GetState() == STATE_DESTROYED) {
			nonGridObject.erase(nonGridObject.begin() + i);
			--i;
		}
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

	//DebugOut(L"----Simon pos Y - cam floor - max map level: %d/ %d/ %d\n", int(simonPosY), camFloor, maxMapLevel);

	int minWidth = tileMap->GetCamLtdMin(camFloor);
	int maxWidth = tileMap->GetCamLtdMax(camFloor);

	//DebugOut(L"---Cam limit min-max, cam level: %d/ %d/ %d\n", tileMap->GetCamLtdMin(camFloor), tileMap->GetCamLtdMax(camFloor), camFloor);

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
	tileMap->Draw({ 0,0 }, 255);
	for (int i = 0; i < nonGridObject.size(); i++) {
		nonGridObject[i]->RenderBoundingBox();
		nonGridObject[i]->Render();
	}
	grid->Render();
	simon->Render();
	hud->Render();
}

/*
	Unload current scene
*/
void CPlayScene::Unload()
{
	for (int i = 0; i < nonGridObject.size(); i++)
		delete nonGridObject[i];
	nonGridObject.clear();
	// ---------------------------------------------------
	// TODO unload grid
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
	case DIK_P:
		simon->SetHealth(16);
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

	if (game->IsKeyDown(DIK_DOWN)) {
		if (simon->IsOnStair()) {
			simon->SetState(SIMON_STATE_DOWNSTAIR);
		}
		else if (simon->GetCollidedStair()) {
			//DebugOut(L"--------simon downstair\n");
			if (simon->GetCollidedStair()->GetNy() < 0) {
				float x, y;
				simon->GetCollidedStair()->GetPosition(x, y);
				simon->SetStair(simon->GetCollidedStair());
				simon->SetPosition(x - 1, y - SIMON_BBOX_HEIGHT + 5);
				simon->SetState(SIMON_STATE_DOWNSTAIR);
			}
			else
				simon->SetState(SIMON_STATE_SIT);
		}
		else
			simon->SetState(SIMON_STATE_SIT);
	}

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