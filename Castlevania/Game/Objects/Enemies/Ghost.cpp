#include "Ghost.h"

LPENEMY Ghost::Clone()
{
	Ghost* clone = new Ghost;
	for (ANIMATION* ani : animations)
	{
		clone->AddAnimation(ani->first->Clone());
	}
	clone->SetAnimation(0);
	return clone;
}

void Ghost::Update(DWORD dt, std::vector<LPGAMEOBJECT>* objects, Simon* simon)
{
	if (alive) ingrid = true;

	float p_x, p_y;
	simon->GetPosition(p_x, p_y);

	if (!appear && p_x >= activeL && p_x <= activeR)
	{
		appear = true;
	}

	Enemy::Update(dt);

	if (appear)
	{
		vx = flip ? 0.04 : -0.04;
	}


	x += dx;
	y += dy;
}

void Ghost::Render(float x, float y)
{
	if (!appear) return;
	Enemy::Render(x, y);
}


void Ghost::Active()
{
	Enemy::Active();
}


void Ghost::Unactive()
{
	Enemy::Unactive();
}