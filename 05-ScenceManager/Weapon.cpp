#include "Weapon.h"



Weapon::Weapon()
{
}


Weapon::~Weapon()
{
}

void Weapon::Update(DWORD dt, vector<LPGAMEOBJECT> *nonGridObject, set<LPGAMEOBJECT> gridObject)
{
	CGameObject::Update(dt, nonGridObject, gridObject);

	x += dx;
	y += dy;

	vector<LPGAMEOBJECT> objects;

	for (auto obj : gridObject)
		objects.push_back(obj);
	for (auto obj : *nonGridObject)
		objects.push_back(obj);

	for (auto iter : objects)
	{
		switch (iter->GetId())
		{
		case ID_TORCH:
		case ID_CANDLE:
		case ID_BAT:
		case ID_BLACK_KNIGHT:
		case ID_GHOST:
		case ID_FLEAMAN:
		case ID_RAVEN:
		case ID_PHANTOM_BAT:
		case ID_BRICK:
		case ID_SKELETON:
		case ID_ZOMBIE:
			float al, at, ar, ab;
			float bl, bt, br, bb;

			GetBoundingBox(al, at, ar, ab);
			iter->GetBoundingBox(bl, bt, br, bb);

			RECT A, B;
			A = { long(al),long(at),long(ar),long(ab) };
			B = { long(bl),long(bt),long(br),long(bb) };

			if (CGame::GetInstance()->IsColliding(A, B)) {
				iter->IsHitted(nonGridObject);
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
