#include "Raven.h"
#include "..\..\Scenes\Scene.h"

Raven::Raven()
{
	hp = 0;
	score = 200;
	timebetweenattack = 5000;
	waittime = 500;
	startwait = -1;
	lastattack = -1;
}

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

void Raven::Update(DWORD dt, std::vector<LPGAMEOBJECT>* objects)
{
	Simon* player = Scenes::GetInstance()->GetScene()->GetPlayer();
	float p_x, p_y;
	player->GetPosition(p_x, p_y);

	Enemy::Update(dt);

	if (!fly && activeL <= p_x && p_x <= activeR)
	{
		fly = true;
		SetAnimation(1);
	}

	if (p_x < x && flip) flip = false;
	if (p_x > x && !flip) flip = true;

	if (fly)
	{
		DWORD curr = GetTickCount();
		if (curr - startwait >= waittime)
		{
			if (!attack)
			{
				vx += flip ? 0.005 : -0.005;
				if (abs(vx) >= 0.2) vx = flip ? 0.1 : -0.1;

				vy = (y <= p_y - 40) ? 0.04 : -0.04;
				if (p_y - 38 > y && y > p_y - 42)
				{
					vy = 0;
				}

				if (curr - lastattack >= timebetweenattack && p_x - 32 <= x && x <= p_x + 48)
				{
					attack = true;
					vy = 0.12;
					vx = flip ? 0.02 : -0.02;
					atk_y = y + 40;
				}
			}
			else
			{
				if (y >= atk_y)
				{
					vy = 0;
					vx = 0;
					startwait = curr;
					lastattack = curr;
					attack = false;
				}
			}
		}

		SetAnimation(attack ? 2 : 1);
	}
	else
	{
		vx = vy = 0;
		SetAnimation(0);
	}

	x += dx;
	y += dy;

	if (!incell && !outview)
		Enemy::CheckView();
}

void Raven::Active()
{
	Enemy::Active();
	fly = false;
}


void Raven::Unactive()
{
	Enemy::Unactive();
}