#include "Hunchback.h"
#include "..\Spawner.h"

LPENEMY Hunchback::Clone()
{
	Hunchback* clone = new Hunchback;
	for (ANIMATION* ani : animations)
	{
		clone->AddAnimation(ani->first->Clone());
	}
	clone->SetAnimation(0);
	return clone;
}

void Hunchback::Update(DWORD dt, std::vector<LPGAMEOBJECT>* objects, Simon* simon)
{
	float p_x, p_y;
	simon->GetPosition(p_x, p_y);

	Enemy::Update(dt);

	if (!jump && activeL <= p_x && p_x <= activeR)
	{
		jump = true;
		leap = true;
		vy = -0.05;
		SetAnimation(1);
	}

	if (leap)
	{
		vx = flip ? 0.15 : -0.15;
	}
	else vx = 0;


	if (leap) vy += dt * 0.0005;
	else vy = 0;

	GameObject::CheckSweptCollision(objects);

}

void Hunchback::Active()
{
	Enemy::Active();
}


void Hunchback::Unactive()
{
	Enemy::Unactive();
}

void Hunchback::ProcessCollision(std::vector<LPCOEVENT>* coEventResults,
	float min_tx, float min_ty, float nx, float ny,
	float& dx, float& dy)
{
	for (LPCOEVENT coEvent : *coEventResults)
	{
		LPGAMEOBJECT o = coEvent->obj;

		if (dynamic_cast<Block*>(o) ||
			dynamic_cast<BreakableBlock*>(o))
		{
			dx = dx * min_tx + nx * 0.4f;
			if (ny == -1) dy = leap ? dy * min_ty + ny * 0.4f : 0;

			if (ny != 0)
			{
				vy = 0;
				if (leap)
				{
					leap = false;
					SetAnimation(0);
				}
			}
		}
	}
}