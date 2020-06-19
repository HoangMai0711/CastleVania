#include "Weapon.h"



Weapon::Weapon()
{
}


Weapon::~Weapon()
{
}

void Weapon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	x += dx;
	y += dy;

	for (auto iter : *coObjects)
	{
		//DebugOut(L"----ID Object: %d\n", iter->GetId());
		switch (iter->GetId())
		{
		case ID_TORCH:
		case ID_CANDLE:
		case ID_BAT:
		case ID_BLACK_KNIGHT:
			float al, at, ar, ab;
			float bl, bt, br, bb;
			GetBoundingBox(al, at, ar, ab);
			//DebugOut(L"---A:  %f-%f-%f-%f\n", al, at, ar, ab);
			iter->GetBoundingBox(bl, bt, br, bb);
			//DebugOut(L"----ID B: %d\n", iter->GetId());
			//DebugOut(L"---B:  %f-%f-%f-%f\n", bl, bt, br, bb);

			RECT A, B;
			A = { long(al),long(at),long(ar),long(ab) };
			B = { long(bl),long(bt),long(br),long(bb) };

			if (CGame::GetInstance()->IsColliding(A, B)) {
				//DebugOut(L"------Whip collide with torch\n");
				iter->IsHitted();
				if (id == ID_DAGGER)
					state = STATE_DESTROYED;
			}
		default:
			break;
		}
	}

	//Delete if weapon is out of screen
	float al, at, ar, ab;
	float bl, bt, br, bb;

	float x = CGame::GetInstance()->GetCamPosX();
	float y = CGame::GetInstance()->GetCamPosY();

	al = x;
	at = y;
	ar = x + SCREEN_WIDTH;
	ab = y + SCREEN_HEIGHT;

	GetBoundingBox(bl, bt, br, bb);

	RECT A, B;
	A = { long(al),long(at),long(ar),long(ab) };
	B = { long(bl),long(bt),long(br),long(bb) };

	if (!CGame::GetInstance()->IsColliding(A, B))
		state = STATE_DESTROYED;
}
