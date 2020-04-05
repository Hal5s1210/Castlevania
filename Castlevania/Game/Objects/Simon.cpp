#include "Simon.h"
#include "..\..\Framework\Game.h"
#include "Spawner.h"

Simon::Simon()
{
	flip = true;
	attack = false;
	crounch = false;
	onair = true;
	jumpStartTime = -1;
}

Simon::~Simon()
{
	delete whip;
}


void Simon::Update(DWORD dt, std::vector<LPGAMEOBJECT>* objects)
{
	GameObject::Update(dt);

	vy += dt * GRAVITY;

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
		y += dy * min_ty + ny * 0.4f;

		if (nx != 0)
		{
			vx = 0;
		}

		if (ny != 0)
		{
			vy = 0;
			if (onair) attack = false;
			onair = false;
		}
		for (LPCOEVENT coEvent : coEventResults)
		{
			LPGAMEOBJECT o = coEvent->obj;

			if (dynamic_cast<Block*>(o))
			{
				
			}
		}

	}


	float cam_x, cam_y;
	int cam_w, cam_h;
	Viewport::GetInstance()->GetPosition(cam_x, cam_y);
	Viewport::GetInstance()->GetSize(cam_w, cam_h);
	if (x < cam_x)
	{
		x = cam_x;
		vx = 0;
	}
	else if (x > cam_x + cam_w - 16)
	{
		x = cam_x + cam_h;
		vx = 0;

	}
}

void Simon::Render(float x, float y)
{
	float X = this->x + x;
	float Y = this->y + y;

	int i = currentAnimation.second;
	LPSPRITE sprite = currentAnimation.first->GetFrame(currentAnimation.second);
	RECT r = sprite->GetRect();
	float fixX = flip ? 16 - (r.right - r.left) : 0;
	float fixY = 32 - (r.bottom - r.top);
	if (flip) X += fixX;
	Y += fixY;

	currentAnimation.first->Draw(currentAnimation.second, X, Y, 255, flip);

	if (attack)
	{
		whip->SetPosition(X + fixX, Y);
		whip->SetFrameIndex(i);
		float w, h;
		w = r.right - r.left;
		h = r.bottom - r.top;

		whip->Render(w, h, flip);

		if (currentAnimation.first->IsFrameReset())
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
		SetAnimation(ATTACK_2);
	else
		SetAnimation(ATTACK_1);
	currentAnimation.second = -1;
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
