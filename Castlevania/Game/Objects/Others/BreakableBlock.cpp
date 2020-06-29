#include "BreakableBlock.h"
#include "..\..\ID.h"
#include "..\..\Scenes\Scene.h"


BreakableBlock::BreakableBlock()
{
	hp = 1;
	invulnerableTime = 300;
	hit = false;
	alive = true;
	item = -1;
}

void BreakableBlock::Render(float x, float y)
{
	if (!alive) return;
	currentAnimation->first->Draw(currentAnimation->second, this->x + x, this->y + y);

	if (Debug::IsEnable())
	{
		float l, t, r, b;
		GetBoundingBox(l, t, r, b);
		Debug::RenderBoundBox(x, y, l, t, r, b);
	}
}

void BreakableBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + 16;
	b = t + 16;
}

LPGAMEOBJECT BreakableBlock::Clone()
{
	BreakableBlock* clone = new BreakableBlock;
	for (ANIMATION* ani : animations)
	{
		clone->AddAnimation(ani->first->Clone());
	}
	clone->SetAnimation(0);
	return clone;
}

bool BreakableBlock::IsHit()
{
	if (GetTickCount() - invulnerableTimeStart >= invulnerableTime)
	{
		hit = false;
	}
	return hit;
}

void BreakableBlock::TakeDamage()
{
	LPSCENE scene = Scenes::GetInstance()->GetScene();

	invulnerableTimeStart = GetTickCount();
	hit = true;

	OutputDebugString(L"Block being hit\n");

	hp -= 1;

	if (hp <= 0)
	{
		hp = 0;
		alive = false;

		LPSPRITE sprite = currentAnimation->first->GetFrame(currentAnimation->second);
		RECT r = sprite->GetRect();

		Effect::AddBreakBlockEffect(r, x, y);

		OutputDebugString(L"Block is break\n");

		if (item > -1)
		{
			LPITEM i = Spawner::GetInstance()->SpawnItem(item, x + ((r.right - r.left) / 2) - 8, y + ((r.bottom - r.top) / 2) - 9);
			scene->AddItem(i);

			OutputDebugString(L"Item Drop!!!\n");
		}
	}
}