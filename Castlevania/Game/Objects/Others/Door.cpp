#include "Door.h"
#include "..\..\..\Framework\Viewport.h"
#include "..\..\Scenes\Scene.h"

Door::Door()
{
	state = 0;
	open = close = false;
	player_move = false;
	active = false;
}

LPGAMEOBJECT Door::Clone()
{
	Door* clone = new Door;
	for (ANIMATION* ani : animations)
	{
		clone->AddAnimation(ani->first->Clone());
	}
	clone->SetAnimation(0);
	return clone;
}

void Door::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + 8;
	b = t + 48;
}

void Door::Render(float x, float y)
{
	float X, Y;
	LPSPRITE sprite = currentAnimation->first->GetFrame(currentAnimation->second);
	RECT rect = sprite->GetRect();
	int w = rect.right - rect.left;
	X = flip ? this->x + 8 - w : this->x;
	Y = this->y;

	currentAnimation->first->Draw(currentAnimation->second, X + x, Y + y, 255, flip);

	if (active && currentAnimation->first->IsFrameReset())
	{
		switch (state)
		{
		case 1: open = true; break;
		case 3: close = true; break;
		}
	}

	if (Debug::IsEnable())
	{
		float l, t, r, b;
		GetBoundingBox(l, t, r, b);
		Debug::RenderBoundBox(x, y, l, t, r, b);
	}
}

void Door::Update(DWORD dt)
{
	if (!active) return;

	Viewport* view = Viewport::GetInstance();
	Simon* player = Scenes::GetInstance()->GetScene()->GetPlayer();

	switch (state)
	{
	case 0:
		if (view->IsReachAutoDest())
		{
			SetAnimation(1);
			state = 1;
		}
		break;

	case 1:
		if (open)
		{
			SetAnimation(2);
			state = 2;
		}
		break;

	case 2:
		if (!player_move)
		{
			float px, py;
			player->GetPosition(px, py);
			px += flip ? -80 : 80;
			player->GoToX(px);
			player->SetState(flip ? Simon::WalkL : Simon::WalkR, true);
			player_move = true;
		}
		if (player->IsReachAutoDest())
		{
			player->SetState(Simon::Idle, true);
			SetAnimation(3);
			state = 3;
		}
		break;

	case 3:
		if (close)
		{
			SetAnimation(0);
			float cx, cy;
			view->GetPosition(cx, cy);
			cx += flip ? -128 : 128;
			view->GoToX(cx);
			view->SetSwitchView(true);
			Debug::DebugOut(L"DestViewX: %f\n", cx);
			state = 4;
		}
		break;
	}
}

void Door::Active()
{
	active = true;
}