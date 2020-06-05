#include "Axe.h"
#include "..\Spawner.h"
#include "..\..\..\Framework\Viewport.h"

Bullet* Axe::Clone()
{
	Axe* clone = new Axe(shooter, target);
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

	GameObject::CheckCollision(objects);

	float cam_x, cam_y;
	int cam_w, cam_h;
	Viewport::GetInstance()->GetSize(cam_w, cam_h);
	Viewport::GetInstance()->GetPosition(cam_x, cam_y);
	if (x < cam_x || x > cam_x + cam_w - 16 || y < cam_y || y> cam_y + cam_w - 16)
	{
		outview = true;
	}
}

void Axe::ProcessSweptAABBCollision(LPGAMEOBJECT o,
	float min_tx, float min_ty, float nx, float ny,
	float& dx, float& dy)
{
	if (dynamic_cast<Candle*>(o))
	{
		Candle* candle = dynamic_cast<Candle*>(o);

		if (candle->IsAlive())
		{
			candle->TakeDamage(damage, this);
		}
	}
	else if (dynamic_cast<Enemy*>(o))
	{
		Enemy* e = dynamic_cast<Enemy*>(o);
			
		if (e->IsAlive())
		{
			e->TakeDamage(damage, this);
		}
	}
}
