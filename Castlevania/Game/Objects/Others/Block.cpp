#include "Block.h"

void Block::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + w;
	b = t + h;
}

void Block::Render(float x, float y)
{

	//float l, t, r, b;
	//GetBoundingBox(l, t, r, b);
	//NSDebug::RenderBoundBox(x, y, l, t, r, b);
}

LPGAMEOBJECT Block::Clone()
{
	return new Block(*this);
}