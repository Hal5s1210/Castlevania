#include "BlackKnight.h"
#include "..\..\Scenes\Scene.h"

BlackKnight::BlackKnight()
{
	hp = 4;
	score = 400;
}

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

void BlackKnight::Brain(DWORD dt)
{
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

	vy += dt * GRAVITY;
}

void BlackKnight::Active()
{
	Enemy::Active();
	hp = 4;
}


void BlackKnight::Unactive()
{
	Enemy::Unactive();
}

void BlackKnight::ProcessSweptAABBCollision(LPGAMEOBJECT o,
	float min_tx, float min_ty, float nx, float ny,
	float& dx, float& dy)
{	
	if (dynamic_cast<Block*>(o) ||
		dynamic_cast<BreakableBlock*>(o))
	{
		dx = dx * min_tx + nx * 0.4f;
		dy = dy * min_ty + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0)
		{
			vy = 0;
		}
	}
}

void BlackKnight::ProcessAABBCollision(LPGAMEOBJECT o)
{
	if (dynamic_cast<Simon*>(o))
	{
		Simon* player = dynamic_cast<Simon*>(o);
		player->TakeHit(2);
	}
}