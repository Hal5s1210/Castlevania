#include "VampireBat.h"
#include "..\..\Scenes\Scene.h"

VampireBat::VampireBat()
{
	hp = 0;
	score = 200;
}

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

void VampireBat::Brain(DWORD dt)
{
	Simon* player = Scenes::GetInstance()->GetScene()->GetPlayer();
	float p_x, p_y;
	player->GetPosition(p_x, p_y);

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
}

void VampireBat::Active()
{
	Enemy::Active();
	fly = false;
	hp = 1;
}


void VampireBat::Unactive()
{
	Enemy::Unactive();
	fly = false;
}


void VampireBat::ProcessAABBCollision(LPGAMEOBJECT o)
{
	if (dynamic_cast<Simon*>(o))
	{
		Simon* player = dynamic_cast<Simon*>(o);
		player->TakeHit(2);
		if (!player->IsInvisible())
			TakeDamage(1, NULL);
	}
}