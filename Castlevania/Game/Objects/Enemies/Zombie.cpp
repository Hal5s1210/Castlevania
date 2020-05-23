#include "Zombie.h"

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

void Zombie::Update(DWORD dt, std::vector<LPGAMEOBJECT>* objects, Simon* simon)
{
	Enemy::Update(dt);

	x += dx;
	y += dy;
}

void Zombie::Active()
{
	Enemy::Active();
}


void Zombie::Unactive()
{
	Enemy::Unactive();
}