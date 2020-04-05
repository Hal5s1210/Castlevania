#include "Block.h"

void Block::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + w;
	b = r + h;
}

LPGAMEOBJECT Block::Clone()
{
	return new Block(*this);
}