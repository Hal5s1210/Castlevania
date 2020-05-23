#include "WhiteSkeleton.h"

LPENEMY WhiteSkeleton::Clone()
{
	WhiteSkeleton* clone = new WhiteSkeleton;
	for (ANIMATION* ani : animations)
	{
		clone->AddAnimation(ani->first->Clone());
	}
	clone->SetAnimation(0);
	return clone;
}

void WhiteSkeleton::Update(DWORD dt, std::vector<LPGAMEOBJECT>* objects, Simon* simon)
{
	Enemy::Update(dt);

	x += dx;
	y += dy;
}

void WhiteSkeleton::Active()
{
	Enemy::Active();
}


void WhiteSkeleton::Unactive()
{
	Enemy::Unactive();
}