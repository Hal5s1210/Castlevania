#include "Portal.h"
#include "..\..\Scenes\Scene.h"

Portal::Portal()
{
	area = -1;
	scene = -1;
	player_x = -1;
	player_y = -1;
	onetime = false;
	active = true;
}

void Portal::Active()
{
	if (area != -1)
	{
		Scenes::GetInstance()->GetScene()->NextArea(area);
		if (player_x != -999 && player_y != -999)
			Scenes::GetInstance()->GetScene()->GetPlayer()->SetPosition(player_x, player_y);
	}
	else if (scene != -1)
	{
		Scenes::GetInstance()->NextScene(scene);
	}

	if (onetime) active = false;
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
	if (Debug::IsEnable())
	{
		float l, t, r, b;
		GetBoundingBox(l, t, r, b);
		Debug::RenderBoundBox(x, y, l, t, r, b);
	}
}
