#define _CRT_SECURE_NO_WARNINGS
#include "HUD.h"

HUD* HUD::__instance;

HUD::HUD()
{
	Load();

	enemyHealth = 16;
}

void HUD::DrawHealth(int id, D3DXVECTOR2 position)
{
	RECT sourceRect = listHealth->at(id);
	CGame::GetInstance()->Draw(position.x, position.y, texHealth, sourceRect.left, sourceRect.top, sourceRect.right, sourceRect.bottom, 255, 0, 1);
}

HUD::~HUD()
{
}

char* IntToChar(int value, int len = 10)
{
	char* c = new char[len + 1];
	c[len] = '\0';
	for (int i = len - 1; i >= 0; i--)
	{
		c[i] = value % 10 + 48;
		value = value / 10;
	}
	return c;
}

void HUD::Draw(D3DXVECTOR2 pos)
{
	//DebugOut(L"----Start draw HUD\n");

	CGame::GetInstance()->Draw(pos.x, pos.y, texBackground, 0, 0, 256, 40, 255, 0, 1);

	// Draw Scores
	text->DrawString("SCORE-", { pos.x + 1, pos.y + 3 });
	text->DrawString(IntToChar(player->GetScore(), 6), { pos.x + 49, pos.y + 3 });

	// Draw Time
	text->DrawString("TIME", { pos.x + 105, pos.y + 3 });
	text->DrawString(IntToChar(player->GetTime(), 3), { pos.x + 141, pos.y + 3 });

	// Draw Stage
	text->DrawString("STAGE", { pos.x + 181, pos.y + 3 });
	char stage[10];
	itoa(CGame::GetInstance()->GetCurrentStage(), stage, 10);
	text->DrawString(stage, { pos.x + 225, pos.y + 3 });

	// Draw Player's Heart
	text->DrawString(IntToChar(player->GetHeart(), 2), { pos.x + 205, pos.y + 16 });

	// Draw Player's Health
	text->DrawString("PLAYER", { pos.x + 1,pos.y + 13 });
	for (int i = 0; i < SIMON_MAX_HEALTH; i++)
	{
		int tmpId = i < player->GetHealth() ? 0 : 1;
		DrawHealth(tmpId, { pos.x + float(55 + i * 5), pos.y + 13 });
	}

	// Draw Enemy's Health
	text->DrawString("ENEMY", { pos.x + 1,pos.y + 23 });
	for (int i = 0; i < 16; i++)
	{
		int tmpId = i < enemyHealth ? 2 : 1;
		DrawHealth(tmpId, { pos.x + float(55 + i * 5), pos.y + 24 });
	}

	// Draw Item
	GetItemSprite()->Draw(pos.x + 165, pos.y + 18, 255, 1);

	// Draw Multishot
	GetMultiShootSprite()->Draw(pos.x + 230, pos.y + 19, 255, 1);

	// Draw Player's Life
	text->DrawString(IntToChar(player->GetLife(), 2), { pos.x + 205, pos.y + 25 });
}

HUD * HUD::GetInstance()
{
	if (__instance == NULL) __instance = new HUD();
	return __instance;
}

void HUD::Render()
{
	Draw({ 0, -HUD_HEIGHT });
}

void HUD::Load()
{
	player = Simon::GetInstance();
	this->texBackground = CTextures::GetInstance()->Get(ID_TEX_HUD);
	this->texHealth = CTextures::GetInstance()->Get(ID_TEX_HEALTH);
	this->text = Text::GetInstance();
	text->Load();
	listHealth = new unordered_map<int, RECT>();
	for (int i = 0; i < 3; i++)
		listHealth->insert(pair<int, RECT>(i, { 5 * i, 0, 5 * (i + 1), 8 }));
}

LPSPRITE HUD::GetItemSprite()
{
	int spriteId;
	int itemId = player->GetSubweaponId();

	switch (itemId)
	{
	case ID_DAGGER:
		spriteId = 12003;
		break;
	case ID_AXE:
		spriteId = 12031;
		break;
	case ID_BOOMERANG:
		spriteId = 12016;
		break;
	default:
		spriteId = 0;
		break;
	}
	//DebugOut(L"---Subweapon Sprite id: %d\n", spriteId);
	return CSprites::GetInstance()->Get(spriteId);
}

LPSPRITE HUD::GetMultiShootSprite()
{
	int spriteId;
	int multiShootLevel = player->GetMultiShotLevel();

	switch (multiShootLevel)
	{
	case 2:
		spriteId = 12050;
		break;
	case 3:
		spriteId = 12051;
		break;
	default:
		spriteId = 0;
		break;
	}
	//DebugOut(L"---Sprite id: %d\n", spriteId);
	return CSprites::GetInstance()->Get(spriteId);
}

void HUD::SetEnemyHealth(int health)
{
	enemyHealth = health;
}
