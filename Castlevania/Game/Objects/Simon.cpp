#include "Simon.h"
#include "..\..\Framework\Game.h"
#include "Generator.h"

Simon::Simon()
{
	whip = new Whip;
	whip->Init(WHIP_PATH);
	attack = false;
	crounch = false;
	onair = true;
}
Simon::~Simon()
{
}

void Simon::Update(DWORD dt, std::vector<LPGAMEOBJECT>* objects)
{
	GameObject::Update(dt);

	if (onair) jumpTime = (GetTickCount() - jumpStartTime) / 1000;
	else jumpTime = 0;

	float g = (jumpTime == 0 ? 1 : jumpTime) * GRAVITY;
	//vy += g * dt;

	std::vector<LPCOEVENT> coEvents;

	CalcPotentialCollisions(objects, coEvents);

	if (coEvents.empty())
	{
		x += dx;
		y += dy;
	}
	else
	{
		std::vector<LPCOEVENT> coEventResults;
		float min_tx, min_ty, nx, ny;

		FilterCollision(coEvents, coEventResults, min_tx, min_ty, nx, ny);

		x += dx * min_tx + nx * 0.4f;
		if (onair)
			y += dy * min_ty + ny * 0.4f;

		for (LPCOEVENT coEvent : coEventResults)
		{
			LPGAMEOBJECT o = coEvent->obj;

			if (dynamic_cast<Block*>(o))
			{
				if (coEvent->nx != 0)
				{
					vx = 0;
				}

				if (coEvent->ny != 0)
				{
					vy = 0;
					if (onair) attack = false;
					onair = false;
				}
			}
		}

	}

	Viewport::GetInstance()->SetPosition(x - 112, 0);
}

void Simon::Render(float x, float y)
{
	float X = this->x + x;
	float Y = this->y + y;

	int i = currentAnimation->CurrentFrameIndex();
	LPSRPITE frame = currentAnimation->GetFrame();
	RECT r = frame->Rect;
	float fixX = flip ? 16 - (r.right - r.left) : 0;
	float fixY = 32 - (r.bottom - r.top);
	if (flip) X += fixX;
	Y += fixY;

	currentAnimation->Draw(X, Y, 255, flip);

	if (attack)
	{
		whip->SetPosition(X + fixX, Y);
		whip->SetFrameIndex(i);
		float w, h;
		w = r.right - r.left;
		h = r.bottom - r.top;

		whip->Render(w, h, flip);

		if (currentAnimation->IsFrameReset())
		{
			attack = false;
			GoIdle();
		}
	}
	
}

void Simon::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + 16;
	b = t + 32;
}

void Simon::GoIdle()
{
	if (attack)
		return;

	if (onair)
	{
		SetAnimation(CROUNCH);
	}
	else
	{
		SetAnimation(IDLE);
		vx = 0;
	}
}


void Simon::GoLeft()
{
	if (attack || onair)
		return;

	SetAnimation(WALK);
	vx = -SIMON_SPEED;
	flip = false;
	
}

void Simon::GoRight()
{
	if (attack || onair)
		return;

	SetAnimation(WALK);
	vx = SIMON_SPEED;
	flip = true;
}

void Simon::Crounch()
{
	if (attack || onair)
		return;

	SetAnimation(CROUNCH);
	vx = 0;
}

void Simon::Jump()
{
	if (!onair)
	{
		vy = JUMP_FORCE;
		jumpStartTime = GetTickCount();
		onair = true;
		SetAnimation(CROUNCH);
	}
}

void Simon::Attack(bool crounch)
{
	if (attack)
		return;

	if (crounch && !onair)
		SetAnimation(ATTACK_1);
	else
		SetAnimation(ATTACK_2);
	currentAnimation->Reset();
	attack = true;
	if (!onair) vx = 0;
}

void Simon::ReadyWeapon()
{
	whip->UseWhip(true);
}

void Simon::ReadySubWeapon()
{
	whip->UseWhip(false);
}
