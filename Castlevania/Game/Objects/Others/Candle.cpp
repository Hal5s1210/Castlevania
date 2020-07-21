#include "Candle.h"
#include "..\..\ID.h"
#include "..\..\Scenes\Scene.h"

Candle::Candle()
{
	hp = 1;
	invulnerableTime = 300;
	hit = false;
	alive = true;
	item = -1;
}


void Candle::Update(DWORD dt)
{

}

void Candle::Render(float x, float y)
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

void Candle::InitSize()
{
	RECT rect = currentAnimation->first->GetFrame(currentAnimation->second)->GetRect();
	w = rect.right - rect.left;
	h = rect.bottom - rect.top;
}

void Candle::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + w;
	b = t + h;
}

LPGAMEOBJECT Candle::Clone()
{
	Candle* clone = new Candle;
	for (ANIMATION* ani : animations)
	{
		clone->AddAnimation(ani->first->Clone());
	}
	clone->SetAnimation(0);
	clone->InitSize();
	return clone;
}

bool Candle::IsHit()
{
	if (GetTickCount() - invulnerableTimeStart >= invulnerableTime)
	{
		hit = false;
	}
	return hit;
}


void Candle::TakeDamage(int damage, LPGAMEOBJECT hitter)
{
	if (IsHit()) return;

	LPSCENE scene = Scenes::GetInstance()->GetScene();

	invulnerableTimeStart = GetTickCount();
	hit = true;

	Effect::AddHitEffect(hitter, this);

	OutputDebugString(L"Candle being hit\n");

	hp -= damage;

	if (hp <= 0)
	{
		hp = 0;
		alive = false;

		LPSPRITE sprite = currentAnimation->first->GetFrame(currentAnimation->second);
		RECT r = sprite->GetRect();

		Effect::AddDeathEffect(r, x, y);

		OutputDebugString(L"Candle is dead\n");

		if (item > -1)
		{
			Item::AddItem(item, r, x, y);

			OutputDebugString(L"Item Drop!!!\n");
		}
	}
}
