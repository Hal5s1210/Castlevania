#include "Dagger.h"
#include "..\Spawner.h"
#include "..\..\Scenes\Scene.h"
#include "..\..\..\Framework\Viewport.h"

LPGAMEOBJECT Dagger::Clone()
{
	Dagger* clone = new Dagger;
	for (ANIMATION* ani : animations)
	{
		clone->AddAnimation(ani->first->Clone());
	}
	clone->SetAnimation(0);
	return clone;
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
					hitted = true;

					torch->TakeDamage(damage);

					//float lo, to, ro, bo;
					//o->GetBoundingBox(lo, to, ro, bo);

					//int eff_x, eff_y;
					//if (!flip) eff_x = ro - 8;
					//else eff_x = lo;
					//eff_y = y + 8;

					//LPEFFECT effect = Spawner::GetInstance()->SpawnEffect(EFFECT_HIT_ID, eff_x, eff_y);
					//Scenes::GetInstance()->GetScene()->AddEffect(effect);
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