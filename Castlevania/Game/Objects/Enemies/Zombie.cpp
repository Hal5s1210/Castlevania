#include "Zombie.h"
#include "..\Spawner.h"
#include "..\..\Scenes\Scene.h"

Zombie::Zombie()
{
	hp = 1;
	score = 100;
}

LPENEMY Zombie::Clone()
{
	Zombie* clone = new Zombie;
	for (ANIMATION* ani : animations)
	{
		clone->AddAnimation(ani->first->Clone());
	}
	clone->SetAnimation(0);
	return clone;
}

void Zombie::Update(DWORD dt, std::vector<LPGAMEOBJECT>* objects)
{
	Simon* player = Scenes::GetInstance()->GetScene()->GetPlayer();
	float p_x, p_y;
	player->GetPosition(p_x, p_y);

	Enemy::Update(dt);

	if (!move && activeL <= p_x && p_x <= activeR)
	{
		move = true;
		vx = flip ? 0.05 : -0.05;
	}

	vy += dt * 0.0005;

	GameObject::CheckSweptCollision(objects);

	if (!incell && !outview)
		Enemy::CheckView();
}

void Zombie::ProcessCollision(std::vector<LPCOEVENT>* coEventResults,
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
			dy = dy * min_ty + ny * 0.4f;
			
			if (nx != 0) vx = 0;
			if (ny != 0)
			{
				vy = 0;
				if (move) vx = flip ? 0.05 : -0.05;
			}
		}
	}
}

void Zombie::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	Enemy::GetBoundingBox(l, t, r, b);
	l++;
	r--;
}

void Zombie::Active()
{
	Enemy::Active();
}


void Zombie::Unactive()
{
	Enemy::Unactive();
}