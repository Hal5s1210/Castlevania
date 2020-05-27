#include "Axe.h"
#include "..\Spawner.h"
#include "..\..\..\Framework\Viewport.h"

LPGAMEOBJECT Axe::Clone()
{
	Axe* clone = new Axe(wielder);
	for (ANIMATION* ani : animations)
	{
		clone->AddAnimation(ani->first->Clone());
	}
	clone->SetAnimation(0);
	return clone;
}


void Axe::Ready(float x, float y, bool flip)
{
	SetFlip(flip);
	if (flip)
	{
		SetPosition(x, y);
		SetSpeed(0.05, -0.25);
	}
	else
	{
		SetPosition(x - 16, y);
		SetSpeed(-0.05, -0.25);
	}
}

void Axe::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + 16;
	b = t + 16;
}

void Axe::Update(DWORD dt, std::vector<LPGAMEOBJECT>* objects)
{
	GameObject::Update(dt);

	vy += 0.0005 * dt;

	GameObject::CheckSweptCollision(objects);

	float cam_x, cam_y;
	int cam_w, cam_h;
	Viewport::GetInstance()->GetSize(cam_w, cam_h);
	Viewport::GetInstance()->GetPosition(cam_x, cam_y);
	if (x < cam_x || x > cam_x + cam_w - 16 || y < cam_y || y> cam_y + cam_w - 16)
	{
		outView = true;
	}
}

void Axe::ProcessCollision(std::vector<LPCOEVENT>* coEventResults,
	float min_tx, float min_ty, float nx, float ny,
	float& dx, float& dy)
{
	for (LPCOEVENT coEvent : *coEventResults)
	{
		LPGAMEOBJECT o = coEvent->obj;

		if (dynamic_cast<Candle*>(o))
		{
			Candle* candle = dynamic_cast<Candle*>(o);

			if (candle->IsAlive())
			{
				candle->TakeDamage(damage, this);
			}
		}
	}
}
