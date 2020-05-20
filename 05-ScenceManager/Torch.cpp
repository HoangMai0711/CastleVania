#include "Torch.h"

Torch::Torch(D3DXVECTOR2 position)
{
	AddAnimation(ID_ANI_TORCH);

	id = ID_TORCH;
	x = position.x;
	y = position.y;
}

Torch::~Torch()
{
}

void Torch::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (state == STATIC_OBJ_STATE_NORMAL)
	{
		l = x;
		t = y;
		r = x + TORCH_BBOX_WIDTH;
		b = y + TORCH_BBOX_HEIGHT;
	}
	else
	{
		l = r = t = b = 0;
	}
	//DebugOut(L"[INFO]Torch BBOX: : %f-%f-%f-%f\n", l, t, r, b);
}

