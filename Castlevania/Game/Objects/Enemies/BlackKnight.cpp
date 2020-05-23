#include "BlackKnight.h"

LPENEMY BlackKnight::Clone()
{
	BlackKnight* clone = new BlackKnight;
	for (ANIMATION* ani : animations)
	{
		clone->AddAnimation(ani->first->Clone());
	}
	clone->SetAnimation(0);
	return clone;
}

void BlackKnight::Update(DWORD dt, std::vector<LPGAMEOBJECT>* objects, Simon* simon)
{
	Enemy::Update(dt);

	if (!stop && ((!flip && x < activeL) || (flip && x > activeR)))
	{
		stop = true;
		startStopTime = GetTickCount();
	}

	if (stop)
	{
		if (GetTickCount() - startStopTime >= stopTime)
		{
			stop = false;
			flip = !flip;
		}
		vx = 0;
		SetAnimation(0);
	}
	else
	{
		vx = flip ? 0.025 : -0.025;
		SetAnimation(1);
	}

	x += dx;
	y += dy;
}

void BlackKnight::Active()
{
	Enemy::Active();
}


void BlackKnight::Unactive()
{
	Enemy::Unactive();
}