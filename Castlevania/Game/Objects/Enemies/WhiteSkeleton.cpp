#include "WhiteSkeleton.h"
#include "..\Spawner.h"
#include "..\..\Scenes\Scene.h"

WhiteSkeleton::WhiteSkeleton()
{
	hp = 2;
	score = 400;
	startstatetime = -1;
	timeeachstate = 400;
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

void WhiteSkeleton::Brain(DWORD dt)
{
	Simon* player = Scenes::GetInstance()->GetScene()->GetPlayer();
	float p_x, p_y;
	player->GetPosition(p_x, p_y);

	if (start && GetTickCount() - startstatetime >= timeeachstate)
	{
		moveforward = !moveforward;
		startstatetime = GetTickCount();
		timeeachstate = 400 - (rand() % 200);
		counttoattack++;
	}

	if (!start && activeL <= p_x && p_x <= activeR)
	{
		start = true;
		counttoattack = 0;
	}

	if (start)
	{
		if (moveforward)
		{
			vx = flip ? 0.05 : -0.05;
		}
		else
		{
			vx = flip ? -0.05 : 0.05;
		}

		if (counttoattack > 5)
		{
			counttoattack = 0;
			Bullet* bone = Spawner::GetInstance()->SpawnBullet(BONE_ID, x + 8, y, flip);
			bone->SetShooter(this);

			Scenes::GetInstance()->GetScene()->AddBullet(bone);
		}
	}

	vy += dt * 0.0005;

	if (x > limitR - 16) x = limitR - 16;
	if (x < limitL) x = limitL;
}

void WhiteSkeleton::Active()
{
	Enemy::Active();
	start = false;
	moveforward = false;
	limitL = default_x - 8;
	limitR = default_x + 24;
}

void WhiteSkeleton::Unactive()
{
	Enemy::Unactive();
}

void WhiteSkeleton::ProcessSweptAABBCollision(LPGAMEOBJECT o,
	float min_tx, float min_ty, float nx, float ny,
	float& dx, float& dy)
{
	if (dynamic_cast<Block*>(o) ||
		dynamic_cast<BreakableBlock*>(o))
	{
		dx = dx * min_tx + nx * 0.4f;
		dy = dy * min_ty + ny * 0.4f;

		if (nx != 0)
		{
			vx = 0;
		}

		if (ny == -1)
		{
			vy = 0;
		}
	}
}

void WhiteSkeleton::ProcessAABBCollision(LPGAMEOBJECT o)
{
	if (dynamic_cast<Simon*>(o))
	{
		Simon* player = dynamic_cast<Simon*>(o);
		player->TakeHit(2);
	}
}