#pragma once
#include <set>
#include "Game.h"
#include "GameObject.h"
#include "GroundObject.h"

class Grid
{
	set<LPGAMEOBJECT>** gridObject;

	int column;
	int row;
public:
	Grid(int row, int column);
	~Grid();

	void AddObject(LPGAMEOBJECT object);
	set< LPGAMEOBJECT> GetCurrentObject();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *nonGridObject, set<LPGAMEOBJECT> gObject);
	void Render();
	//void GetGroundObject(vector<LPGAMEOBJECT>* objects);
};

