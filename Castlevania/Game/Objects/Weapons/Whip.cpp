#include "Whip.h"
#include "..\Spawner.h"
#include "..\..\Scenes\Scene.h"
#include "..\..\..\Framework\Collision.h"

Whip::Whip()
{
	level = 1;
	damage = 1;
}

void Whip::Update(DWORD dt, std::vector<LPGAMEOBJECT>* objects)
{
	if (index != 2) return;

	CheckCollision(objects);
}

void Whip::Render(float x, float y)
{
	float X = this->x;
	float Y = this->y;

	LPSPRITE sprite = currentAnimation->first->GetFrame(currentAnimation->second);
	RECT rect = sprite->GetRect();
	int w = rect.right - rect.left;

	if (!isWhip)
	{
		if (index == 2)
		{
			if (!flip) X -= w;
			currentAnimation->first->Draw(currentAnimation->second, X + x, Y + y, 255, flip);

			if (Debug::IsEnable())
			{
				float l, t, r, b;
				GetBoundingBox(l, t, r, b);
				Debug::RenderBoundBox(x, y, l, t, r, b);
			}
		}
	}
	else
	{
		if (index < 2)
		{
			if (!flip)X += 16;
			else X -= 16 + w;
		}
		else if (index == 2)
		{
			if (!flip) X -= w;
		}
		currentAnimation->first->Draw(currentAnimation->second, X + x, Y + y, 255, flip);

		if (Debug::IsEnable())
		{
			float l, t, r, b;
			GetBoundingBox(l, t, r, b);
			Debug::RenderBoundBox(x, y, l, t, r, b);
		}
	}
}

void Whip::ProcessAABBCollision(LPGAMEOBJECT o)
{
	if (dynamic_cast<Candle*>(o))
	{
		Candle* candle = dynamic_cast<Candle*>(o);
		if (candle->IsAlive() && !candle->IsHit())
		{
			candle->TakeDamage(damage, this);
		}
	}
	else if (dynamic_cast<BreakableBlock*>(o))
	{
		BreakableBlock* block = dynamic_cast<BreakableBlock*>(o);
		if (block->IsAlive() && !block->IsHit())
		{
			block->TakeDamage();
		}

	}
	else if (dynamic_cast<LPENEMY>(o))
	{
		LPENEMY e = dynamic_cast<LPENEMY>(o);
		if (e->IsAlive())
		{
			e->TakeDamage(damage, this);
		}
	}
}

void Whip::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (isWhip && index == 2)
	{
		LPSPRITE sprite = currentAnimation->first->GetFrame(currentAnimation->second);
		RECT rect = sprite->GetRect();
		int w = rect.right - rect.left;
		int h = rect.bottom - rect.top;

		l = x;

		if (!flip) l -= w;

		t = y + 2;
		r = l + w;
		b = t + h - 2;
	}
	else
	{
		l = r = t = b = 0;
	}

}

void Whip::SetFrameIndex(int i)
{
	index = i;

	if (!isWhip)
	{
		SetAnimation(0);
		return;
	}

	if (level == 1)
	{
		switch (i)
		{
		case -1:
		case 0:
			SetAnimation(1);
			break;
		case 1:
			SetAnimation(2);
			break;
		case 2:
			SetAnimation(3);
			break;
		}
	}
	else if (level == 2)
	{
		switch (i)
		{
		case -1:
		case 0:
			SetAnimation(4);
			break;
		case 1:
			SetAnimation(5);
			break;
		case 2:
			SetAnimation(6);
			break;
		}
	}
	else if (level == 3)
	{
		switch (i)
		{
		case -1:
		case 0:
			SetAnimation(7);
			break;
		case 1:
			SetAnimation(8);
			break;
		case 2:
			SetAnimation(9);
			break;
		}
	}
}
