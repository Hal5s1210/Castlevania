#include "Stair.h"

void Stair::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + 16;
	b = t + 16;
}

void Stair::Render(float x, float y)
{
	float l, t, r, b;
	GetBoundingBox(l, t, r, b);
	NSDebug::RenderBoundBox(x, y, l, t, r, b);
}