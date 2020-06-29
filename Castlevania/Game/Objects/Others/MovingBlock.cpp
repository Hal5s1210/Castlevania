#include "MovingBlock.h"

LPGAMEOBJECT MovingBlock::Clone()
{
	MovingBlock* clone = new MovingBlock;
	for (ANIMATION* ani : animations)
	{
		clone->AddAnimation(ani->first->Clone());
	}
	clone->SetAnimation(0);
	return clone;
}

void MovingBlock::Update(DWORD dt)
{
	vx = flip ? 0.03 : -0.03;
	GameObject::Update(dt);

	x += dx;
	y += dy;

	if ((vx < 0 && x <= limit_left) || (vx > 0 && x + 32 >= limit_right))
	{
		flip = !flip;
	}
}

void MovingBlock::Render(float x, float y)
{
	currentAnimation->first->Draw(currentAnimation->second, this->x + x, this->y + y + 1);

	if (Debug::IsEnable())
	{
		float l, t, r, b;
		GetBoundingBox(l, t, r, b);
		Debug::RenderBoundBox(x, y, l, t, r, b);
	}
}

void MovingBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + 32;
	b = t + 8;
}