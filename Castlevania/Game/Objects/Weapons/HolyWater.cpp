#include "HolyWater.h"
#include "..\Spawner.h"
#include "..\..\..\Framework\Viewport.h"


LPGAMEOBJECT HolyWater::Clone()
{
	HolyWater* clone = new HolyWater(wielder);
	for (ANIMATION* ani : animations)
	{
		clone->AddAnimation(ani->first->Clone());
	}
	clone->SetAnimation(0);
	return clone;
}

void HolyWater::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + 8;
	b = t + 8;
}

void HolyWater::Ready(float x, float y, bool flip)
{
	SetFlip(flip);
	if (flip)
	{
		SetPosition(x, y);
		SetSpeed(0.1, -0.01);
	}
	else
	{
		SetPosition(x - 16, y);
		SetSpeed(-0.1, -0.01);
	}

	burnTimeStart = -1;
	burnTime = 1000;
}


void HolyWater::Update(DWORD dt, std::vector<LPGAMEOBJECT>* objects)
{
	GameObject::Update(dt);

	std::vector<LPCOEVENT> coEvents;

	if (!burning && !startBurn)
		vy += 0.0005 * dt;

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

		for (LPCOEVENT coEvent : coEventResults)
		{
			LPGAMEOBJECT o = coEvent->obj;

			if (dynamic_cast<Torch*>(o))
			{
				Torch* torch = dynamic_cast<Torch*>(o);

				if (torch->IsAlive() && !torch->IsHitted())
				{
					torch->TakeDamage(damage, this);
				}
			}
			else if (dynamic_cast<Block*>(o))
			{
				if (!startBurn)
				{
					dx = dx * min_tx + nx * 0.4f;
					dy = dy * min_ty + ny * 0.4f;

					startBurn = true;
					SetSpeed(0, 0);
					SetAnimation(1);
					y -= 8;
				}
			}
		}

		x += dx;
		y += dy;
	}

	float cam_x, cam_y;
	int cam_w, cam_h;
	Viewport::GetInstance()->GetSize(cam_w, cam_h);
	Viewport::GetInstance()->GetPosition(cam_x, cam_y);
	if (x < cam_x || x > cam_x + cam_w - 16 || y < cam_y || y> cam_y + cam_w - 16)
	{
		outView = true;
	}
}

void HolyWater::Render(float x, float y)
{
	Weapon::Render(x, y);

	if (currentAnimation->first->IsFrameReset())
	{
		if (startBurn)
		{
			startBurn = false;
			burning = true;
			SetAnimation(2);
			this->x -= 4;
			burnTimeStart = GetTickCount();
		}
		else if (burning)
		{
			if (GetTickCount() - burnTimeStart >= burnTime)
			{
				hit = true;
			}
		}
	}
}
