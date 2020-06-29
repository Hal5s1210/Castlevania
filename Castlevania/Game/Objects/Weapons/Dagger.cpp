#include "Dagger.h"
#include "..\Spawner.h"
#include "..\..\Scenes\Scene.h"
#include "..\..\..\Framework\Viewport.h"

Bullet* Dagger::Clone()
{
	Dagger* clone = new Dagger(shooter, target);
	for (ANIMATION* ani : animations)
	{
		clone->AddAnimation(ani->first->Clone());
	}
	clone->SetAnimation(0);
	return clone;
}

void Dagger::Ready(float x, float y, bool flip)
{
	SetFlip(flip);
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

void Dagger::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y + 4;
	r = l + 16;
	b = t + 8;
}

void Dagger::Update(DWORD dt, std::vector<LPGAMEOBJECT>* objects)
{
	GameObject::Update(dt);

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
void Dagger::ProcessAABBCollision(LPGAMEOBJECT o)
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

void Dagger::ProcessSweptAABBCollision(LPGAMEOBJECT o,
	float min_tx, float min_ty, float nx, float ny,
	float& dx, float& dy)
{
	if (dynamic_cast<Candle*>(o))
	{
		Candle* candle = dynamic_cast<Candle*>(o);

		if (candle->IsAlive())
		{
			hit = true;
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