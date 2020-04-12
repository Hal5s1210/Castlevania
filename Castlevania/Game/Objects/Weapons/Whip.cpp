#include "Whip.h"
#include "..\Spawner.h"
#include "..\..\..\Framework\Collision.h"

Whip::Whip()
{
	level = 3;
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

void Whip::Update(DWORD dt, std::vector<LPGAMEOBJECT>* objects)
{
	std::vector<LPGAMEOBJECT> coObjects;

	for (LPGAMEOBJECT obj : (*objects))
	{
		float l, t, r, b;
		GetBoundingBox(l, t, r, b);
		float lo, to, ro, bo;
		obj->GetBoundingBox(lo, to, ro, bo);

		if (Collision::AABB(l, t, r, b, lo, to, ro, bo))
			coObjects.push_back(obj);
	}

	if (!coObjects.empty())
	{
		bool hit = false;
		for (LPGAMEOBJECT obj : coObjects)
		{
			if (dynamic_cast<Torch*>(obj))
				hit = true;
		}
		if (hit)
			OutputDebugString(L"Whip hit a torch\n");
	}
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

		float l, t, r, b;
		GetBoundingBox(l, t, r, b);
		NSDebug::RenderBoundBox(x, y, l, t, r, b);
	}
}

void Whip::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (index == 2)
	{
		LPSPRITE sprite = currentAnimation->first->GetFrame(currentAnimation->second);
		RECT rect = sprite->GetRect();
		int w = rect.right - rect.left;
		int h = rect.bottom - rect.top;

		l = x;

		if (!flip) l -= w;

		t = y;
		r = l + w;
		b = t + h;
	}
	else
	{
		l = r = t = b = 0;
	}

}
