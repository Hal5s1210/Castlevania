#include "Block.h"
#include "..\..\..\Framework\Debug.h"

void Block::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + w;
	b = t + h;
}

void Block::Render(float x, float y)
{
	/*float X = this->x + x;
	float Y = this->y + y;
	float l, t, r, b;
	GetBoundingBox(l, t, r, b);
	NSDebug::RenderBoundBox(X, Y, l, t, r, b);*/
}


LPGAMEOBJECT Block::Clone()
{
	return new Block(*this);
}