#include "Stair.h"
#include "..\Spawner.h"
#include "..\..\Scenes\Scene.h"
#include "..\..\..\Framework\Collision.h"

void Stair::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + 16;
	b = t + 16;
}

void Stair::Update(DWORD dt)
{
	float l, t, r, b;
	GetBoundingBox(l, t, r, b);

	Simon* player = Scenes::GetInstance()->GetScene()->GetPlayer();
	float pl, pt, pr, pb;
	player->GetBoundingBox(pl, pt, pr, pb);

	if (Collision::AABB(l, t, r, b, pl, pt, pr, pb))
	{
		player->HitStair(this);
	}
}

void Stair::Render(float x, float y)
{
	if (Debug::IsEnable())
	{
		float l, t, r, b;
		GetBoundingBox(l, t, r, b);
		Debug::RenderBoundBox(x, y, l, t, r, b);
	}
}