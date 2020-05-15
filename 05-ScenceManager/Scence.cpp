#include "Scence.h"

CScene::CScene(int id, LPCWSTR filePath)
{
	this->id = id;
	LPCWSTR c_filePath = _wcsdup(filePath);
	this->sceneFilePath = c_filePath;
}