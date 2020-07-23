#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scence.h"
#include "GameObject.h"
#include "Brick.h"
#include "Simon.h"
#include "TileMap.h"
#include "Wall.h"
#include "Portal.h"
#include "Torch.h"
#include "HiddenObject.h"
#include "Item.h"
#include "BigHeart.h"
#include "ItemDagger.h"
#include "Candle.h"
#include "ItemBoomerang.h"
#include "Stair.h"
#include "Bat.h"
#include "BlackKnight.h"
#include "MovingBrick.h"
#include "Ghost.h"
#include "Fleaman.h"
#include "Raven.h"
#include "ZombieZone.h"
#include "Skeleton.h"
#include "PhantomBat.h"
#include "Grid.h"
#include "GroundObject.h"
#include "Brick.h"
#include "HUD.h"
#include "OneWayWall.h"
#include "ActiveBox.h"

class CPlayScene: public CScene
{
protected: 				// A play scene has to have player, right? 
	Simon *simon;

	vector<LPGAMEOBJECT> nonGridObject;
	LPTILEMAP tileMap;
	CGame* game;
	Grid* grid;
	LPHUD hud;

	//void ReadFile_FONTS(LPTSTR path);

	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	//void _ParseSection_OBJECTS(string line);
public: 
	CPlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	void LoadAnimations();

	friend class CPlayScenceKeyHandler;
};

class CPlayScenceKeyHandler : public CScenceKeyHandler
{
public: 
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CPlayScenceKeyHandler(CScene *s) :CScenceKeyHandler(s) {};
};

