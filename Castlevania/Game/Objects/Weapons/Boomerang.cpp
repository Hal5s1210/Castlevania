#include "Boomerang.h"
#include "..\Spawner.h"
#include "..\..\Scenes\Scene.h"
#include "..\..\..\Framework\Viewport.h"

LPGAMEOBJECT Boomerang::Clone()
{
	Boomerang* clone = new Boomerang;
	for (ANIMATION* ani : animations)
	{
		clone->AddAnimation(ani->first->Clone());
	}
	clone->SetAnimation(0);
	return clone;
}


void Boomerang::Ready(float x, float y, bool flip)
{
	comeback = false;
	SetFlip(!flip);
	if (flip)
	{
		SetPosition(x, y);
		SetSpeed(0.2, 0);
	}
	else
	{
		SetPosition(x - 16, y);
		SetSpeed(-0.2, 0);
	}
}

void Boomerang::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + 16;
	b = t + 16;
}

void Boomerang::Update(DWORD dt, std::vector<LPGAMEOBJECT>* objects)
{
	GameObject::Update(dt);

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

		for (LPCOEVENT coEvent : coEventResults)
		{
			LPGAMEOBJECT o = coEvent->obj;

			if (dynamic_cast<Torch*>(o))
			{
				Torch* torch = dynamic_cast<Torch*>(o);

				if (torch->IsAlive() && !torch->IsHitted())
				{
					torch->TakeDamage(damage);
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
		if (comeback)
		{
			outView= true;
		}
		else 
		{
			comeback = true;
			vx = -vx;
		}
	}

}
