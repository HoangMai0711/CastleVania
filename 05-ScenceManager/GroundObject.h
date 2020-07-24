#pragma once
#include "GameObject.h"

class GroundObject :
	public CGameObject
{
	vector<D3DXVECTOR2> gridPosition;
public:
	GroundObject();
	~GroundObject();

	void SetGridPositon(vector<D3DXVECTOR2> gridPos) { this->gridPosition = gridPos; }
	vector<D3DXVECTOR2> GetGridPosition() { return this->gridPosition; }
	void AddGridPositon(D3DXVECTOR2 gridPos) { this->gridPosition.push_back(gridPos); }
	virtual void Render() = 0;
};

typedef GroundObject* LPGROUNDOBJECT;

