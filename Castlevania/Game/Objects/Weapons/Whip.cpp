#include "Whip.h"

Whip::Whip()
{
	level = 1;
}

void Whip::SetFrameIndex(int i)
{
	int index = i;

	if (!isWhip)
	{
		SetAnimation(0);
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


void Whip::Render(float x, float y, bool flip)
{
	float X = this->x;
	float Y = this->y;

	LPSRPITE frame = currentAnimation->GetFrame();
	RECT r = frame->Rect;
	int w = r.right - r.left;

	if (!isWhip)
	{
		if (index == 2)
		{
			if (!flip) X -= w;
			else X += x;
			currentAnimation->Draw(X, Y, 255, flip);
		}
		return;
	}
	else
	{
		if (index <= 0)
		{
			if (!flip)X += x;
		}
		else if (index == 1)
		{
			if (!flip) X += x;
			else X -= w;
		}
		else if (index == 2)
		{
			if (!flip) X -= w;
			else X += x;
		}
		currentAnimation->Draw(X, Y, 255, flip);
	}
}

void Whip::GetBoundingBox(float& l, float& t, float& r, float& b)
{
}
