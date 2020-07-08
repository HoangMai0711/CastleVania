#include "Grid.h"


Grid::Grid(int row, int column)
{
	this->row = row;
	this->column = column;

	gridObject = new set<LPGAMEOBJECT>*[row];
	for (int i = 0; i < row; i++) {
		gridObject[i] = new set<LPGAMEOBJECT>[column];
	}
}

Grid::~Grid()
{
}

void Grid::AddObject(LPGAMEOBJECT object)
{
	try {
		GroundObject* castedGroundObject = dynamic_cast<GroundObject*>(object);
		vector<D3DXVECTOR2> gPos = castedGroundObject->GetGridPosition();
		for (D3DXVECTOR2 pos : gPos) {
			gridObject[int(pos.x)][int(pos.y)].insert(object);
		}
	}
	catch (exception e) {
		//do nothing
	}
}

set<LPGAMEOBJECT> Grid::GetCurrentObject()
{
	set<LPGAMEOBJECT> currentGameObject;

	CGame* camPosition = CGame::GetInstance();

	int camX = camPosition->GetCamPosX();
	int camY = camPosition->GetCamPosY();

	int beginCol = camX / GRID_WIDTH;
	int endCol = (camX + SCREEN_WIDTH) / GRID_WIDTH;
	int beginRow = camY / GRID_HEIGHT;
	int endRow = (camY + SCREEN_HEIGHT) / GRID_HEIGHT;

	endCol = endCol > (column - 1) ? (column - 1) : endCol;
	endRow = endRow > (row - 1) ? (row - 1) : endRow;

	for (int i = beginRow; i <= endRow; ++i)
		for (int j = beginCol; j <= endCol; ++j)
			for (auto obj : gridObject[i][j])
				currentGameObject.insert(obj);

	return currentGameObject;
}

void Grid::Update(DWORD dt, vector<LPGAMEOBJECT> *nonGridObject, set<LPGAMEOBJECT> gObject) 
{
	set<LPGAMEOBJECT> currentObject = GetCurrentObject();

	for (auto obj : currentObject) {
		if (obj->GetState() == STATE_DESTROYED) {
			try {
				GroundObject* castedGroundObject = dynamic_cast<GroundObject*>(obj);
				vector<D3DXVECTOR2> gPos = castedGroundObject->GetGridPosition();
				for (D3DXVECTOR2 pos : gPos) {
					gridObject[int(pos.x)][int(pos.y)].erase(obj);
				}
			}
			catch (exception e) {
				// do nothing
			}
		}
		else {
			obj->Update(dt, nonGridObject, gObject);
		}
	}
}
void Grid::Render()
{
	for (auto obj : GetCurrentObject())
		obj->Render();
}
