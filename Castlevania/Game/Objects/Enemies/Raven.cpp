#include "Raven.h"

LPENEMY Raven::Clone()
{
	Raven* clone = new Raven;
	for (ANIMATION* ani : animations)
	{
		clone->AddAnimation(ani->first->Clone());
	}
	clone->SetAnimation(0);
	return clone;
}

void Raven::Update(DWORD dt, std::vector<LPGAMEOBJECT>* objects, Simon* simon)
{
	Enemy::Update(dt);

	x += dx;
	y += dy;
}

void Raven::Active()
{
	Enemy::Active();
}


void Raven::Unactive()
{
	Enemy::Unactive();
}