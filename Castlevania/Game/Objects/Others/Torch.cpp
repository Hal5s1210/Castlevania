#include "Torch.h"

void Torch::Update(DWORD dt)
{

}

void Torch::Render(float x, float y)
{
	SetAnimation(0);
	currentAnimation->first->Draw(currentAnimation->second, this->x + x, this->y + y);

	float l, t, r, b;
	GetBoundingBox(l, t, r, b);
	NSDebug::RenderBoundBox(x, y, l, t, r, b);
}

void Torch::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + 16;
	b = t + 32;
}

LPGAMEOBJECT Torch::Clone()
{
	return new Torch(*this);
}
