#include "WhiteSkeleton.h"
#include "..\Spawner.h"
#include "..\..\Scenes\Scene.h"

WhiteSkeleton::WhiteSkeleton()
{
	hp = 2;
	score = 400;
	startstatetime = -1;
	timeeachstate = 200;
}

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

void WhiteSkeleton::Update(DWORD dt, std::vector<LPGAMEOBJECT>* objects)
{
	Simon* player = Scenes::GetInstance()->GetScene()->GetPlayer();
	float p_x, p_y;
	player->GetPosition(p_x, p_y);

	Enemy::Update(dt);

	if (0 <= state && state <= 4 && GetTickCount() - startstatetime >= timeeachstate)
	{
		if (!jump)
			state = rand() % 5;
		startstatetime = GetTickCount();
	}

	if (state == -1 && activeL <= p_x && p_x <= activeR)
	{
		state = 2;
	}

	switch (state)
	{
	case 1:
		vx = flip ? 0.04 : -0.04;
		break;
	case 2:
		vx = flip ? -0.04 : 0.04;
		break;
	case 3:
		//attack;
		vx = 0;
		break;
	case 4:
		if (!jump)
		{
			vy = -0.2;
			jump = true;
		}
		vx = flip ? 0.08 : -0.08;
		break;
	case 5:
		if (!jump)
		{
			vy = -0.2;
			jump = true;
		}
		vx = flip ? -0.08 : 0.08;
		break;
	default:
		vx = 0;
		break;
	}

	vy += dt * 0.0005;

	GameObject::CheckSweptCollision(objects);

	if (state < 4 && x > limitR - 16)
	{
		x = limitR - 16;
		y = default_y;
		vx = -vx;
	}
	if (state < 4 && x < limitL)
	{
		x = limitL;
		y = default_y;
		vx = -vx;
	}

	if (!incell && !outview)
		Enemy::CheckView();
}


void WhiteSkeleton::ProcessCollision(std::vector<LPCOEVENT>* coEventResults,
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
			dy = !jump ? dy * min_ty + ny * 0.4f : 0;

			if (nx != 0)
			{
				vx = 0;
			}
			if (ny == -1)
			{
				vy = 0;
				if (state == 4)
				{
					state = 5;
				}
				else if (state == 5)
				{
					state = rand() % 4;
				}
				jump = false;
			}
		}
	}
}

void WhiteSkeleton::Active()
{
	Enemy::Active();
	state = -1;
	limitL = default_x - 8;
	limitR = default_x + 24;
}


void WhiteSkeleton::Unactive()
{
	Enemy::Unactive();
}