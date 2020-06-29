#include "Boomerang.h"
#include "..\Spawner.h"
#include "..\..\Scenes\Scene.h"
#include "..\..\..\Framework\Viewport.h"

Bullet* Boomerang::Clone()
{
	Boomerang* clone = new Boomerang(shooter, target);
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
	SetFlip(flip);
	if (flip)
	{
		SetPosition(x, y);
		SetSpeed(0.2, 0);
		returnPoint = x + 8 + 64;
	}
	else
	{
		SetPosition(x - 16, y);
		SetSpeed(-0.2, 0);
		returnPoint = x - 8 - 64;
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

	//colision with wielder
	if (back)
	{
		LPCOEVENT e = SweptAABBEx(shooter);
		if (e->t > 0 && e->t <= 1)
		{
			hit = true;
		}
		delete e;
	}

	GameObject::CheckCollision(objects);

	if ((flip && x >= returnPoint) || (!flip && x <= returnPoint))
	{
		comeback = true;
	}

	if (comeback && !back)
	{
		if (flip)
		{
			vx += -0.02;
			if (vx < -0.2)
			{
				vx = -0.2;
				back = true;
			}
		}
		else
		{
			vx += 0.02;
			if (vx > 0.2)
			{
				vx = 0.2;
				back = true;
			}
		}
	}

	float cam_x, cam_y;
	int cam_w, cam_h;
	Viewport::GetInstance()->GetSize(cam_w, cam_h);
	Viewport::GetInstance()->GetPosition(cam_x, cam_y);
	if (x < cam_x || x > cam_x + cam_w - 16 || y < cam_y || y> cam_y + cam_w - 16)
	{
		if (back)
		{
			outview= true;
		}
		else if(!comeback)
		{
			back = true;
			vx = -vx;
		}
	}

}

void Boomerang::ProcessAABBCollision(LPGAMEOBJECT o)
{
	if (dynamic_cast<Enemy*>(o))
	{
		Enemy* e = dynamic_cast<Enemy*>(o);

		if (e->IsAlive())
		{
			e->TakeDamage(damage, this);
		}
	}
}

void Boomerang::ProcessSweptAABBCollision(LPGAMEOBJECT o,
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