#include "Portal.h"
#include "..\..\Scenes\Scene.h"

void Portal::Active()
{
	if (area != -1)
	{
		Scenes::GetInstance()->GetScene()->NextArea(area);
	}
	else if (scene != -1)
	{

		Scenes::GetInstance()->NextScene(scene);
	}
}


void Portal::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + w;
	b = t + h;
}

void Portal::Render(float x, float y)
{
	float l, t, r, b;
	GetBoundingBox(l, t, r, b);
	NSDebug::RenderBoundBox(x, y, l, t, r, b);
}
