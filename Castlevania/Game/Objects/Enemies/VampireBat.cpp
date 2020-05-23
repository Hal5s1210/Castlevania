#include "VampireBat.h"

LPENEMY VampireBat::Clone()
{
	VampireBat* clone = new VampireBat;
	for (ANIMATION* ani : animations)
	{
		clone->AddAnimation(ani->first->Clone());
	}
	clone->SetAnimation(0);
	return clone;
}

void VampireBat::Update(DWORD dt, std::vector<LPGAMEOBJECT>* objects, Simon* simon)
{
	Enemy::Update(dt);

	float p_x, p_y;
	simon->GetPosition(p_x, p_y);
	if (activeL <= p_x && p_x <= activeR &&
		default_y <= p_y && p_y <= default_y + 64)
	{
		if (!fly)
		{
			fly = true;
			SetAnimation(1);
			start_pos_y = y;
			player_pos_y = p_y + 16;
		}
	}

	if (fly)
	{
		vx = flip ? 0.08 : -0.08;
		vy = 0.08 * (1.f - (y - start_pos_y) / (player_pos_y - start_pos_y));
	}
	else
	{
		vx = vy = 0;
	}

	x += dx;
	y += dy;
}

void VampireBat::Active()
{
	Enemy::Active();
	fly = false;
}


void VampireBat::Unactive()
{
	Enemy::Unactive();
	fly = false;
}