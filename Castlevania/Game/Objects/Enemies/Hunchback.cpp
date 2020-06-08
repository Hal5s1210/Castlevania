#include "Hunchback.h"
#include "..\Spawner.h"
#include "..\..\Scenes\Scene.h"

Hunchback::Hunchback()
{
	hp = 1;
	score = 500;
	timebetweenjumps = 200;
	lastjump = -1;
	land = false;
}

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

void Hunchback::Update(DWORD dt, std::vector<LPGAMEOBJECT>* objects)
{
	if (!alive || !active || outview) return;

	Simon* player = Scenes::GetInstance()->GetScene()->GetPlayer();
	float p_x, p_y;
	player->GetPosition(p_x, p_y);

	Enemy::Update(dt);

	if (!attack && activeL <= p_x && p_x <= activeR)
	{
		attack = true;
		jump = 1;
	}

	if (p_x < x && flip) flip = false;
	if (p_x > x && !flip) flip = true;

	if (attack && land)
	{
		if (GetTickCount() - lastjump >= timebetweenjumps)
		{
			switch (jump)
			{
			case 1:
				vx = flip ? 0.15 : -0.15;
				vy = -0.1;
				land = false;
				SetAnimation(1);
				break;
			case 2:
				vx = flip ? 0.08 : -0.08;
				vy = -0.2;
				land = false;
				SetAnimation(1);
				break;
			default:
				SetAnimation(0);
				land = true;
				lastjump = GetTickCount();
				vx = vy = 0;
				break;
			}

			jump = rand() % 3;
		}
	}

	vy += dt * 0.0005;

	//GameObject::UpdatePosition();

	if (!incell && !outview)
		Enemy::CheckView();
}

void Hunchback::Active()
{
	Enemy::Active();
	hp = 1;
	attack = false;
}


void Hunchback::Unactive()
{
	Enemy::Unactive();
}

void Hunchback::ProcessSweptAABBCollision(LPGAMEOBJECT o,
	float min_tx, float min_ty, float nx, float ny,
	float& dx, float& dy)
{
	if (dynamic_cast<Block*>(o) ||
		dynamic_cast<BreakableBlock*>(o))
	{
		dx = dx * min_tx + nx * 0.4f;
		dy = jump > 0 ? dy * min_ty + ny * 0.4f : 0;

		if (ny == -1)
		{
			vx = vy = 0;
			if (!land)
			{
				lastjump = GetTickCount();
				land = true;
				SetAnimation(0);
			}
		}
	}
}

void Hunchback::ProcessAABBCollision(LPGAMEOBJECT o)
{
	if (dynamic_cast<Simon*>(o))
	{
		Simon* player = dynamic_cast<Simon*>(o);
		player->TakeHit(2);
	}
}