#include "Text.h"

Text* Text::__instance;

Text::Text()
{
	Load();

	charWidth = 8;
	charHeight = 8;
	column = 16;
	numOfChar = 48;
	int listID[48] = { 48,49,50,51,52,53,54,55,56,57,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,46,39,33,45,34,-1,44,58,35,32,64,63 };

	for (int i = 0; i < numOfChar; i++) {
		int top = 8 + (i / column)*charHeight;
		int left = 8 + (i%column)*charWidth;
		RECT tmpRect = { left, top, left + charWidth, top + charHeight };
		listChar.insert(pair<int, RECT>(listID[i], tmpRect));
	}
}

void Text::DrawChar(char c, D3DXVECTOR2 position)
{
	RECT sourceRect = listChar[c];
	CGame::GetInstance()->Draw(position.x, position.y, texture, sourceRect.left, sourceRect.top, sourceRect.right, sourceRect.bottom, 255, 0, 1);
}


Text::~Text()
{
}

Text * Text::GetInstance()
{
	if (__instance == NULL)
		__instance = new Text();
	return __instance;
}

void Text::DrawString(char * s, D3DXVECTOR2 position)
{
	//DebugOut(L"----Start draw string-----------\n");
	for (int i = 0; i < strlen(s); i++)
		DrawChar(s[i], { position.x + i * charWidth, position.y });
	//DebugOut(L"----Draw string: %s\n", ToLPCWSTR(s));
}

void Text::Load()
{
	this->texture = CTextures::GetInstance()->Get(ID_TEX_FONT);
}
