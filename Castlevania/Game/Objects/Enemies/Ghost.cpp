#include "Ghost.h"
#include "..\..\Scenes\Scene.h"

Ghost::Ghost()
{
	hp = 3;
	score = 300;
}

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

void Ghost::Brain(DWORD dt)
{
	Simon* player = Scenes::GetInstance()->GetScene()->GetPlayer();
	float p_x, p_y;
	player->GetPosition(p_x, p_y);

	if (!appear && hp > 0 && p_x >= activeL && p_x <= activeR)
	{
		appear = true;
	}

	if (appear)
	{
		if (p_x < x && flip) flip = false;
		if (p_x > x && !flip) flip = true;

		vx = flip ? 0.03 : -0.03;
		vy = p_y > y ? 0.02 : -0.02;
	}
}

void Ghost::Render(float x, float y)
{
	if (!appear) return;
	Enemy::Render(x, y);
}


void Ghost::Active()
{
	Enemy::Active();
	appear = false;
	hp = 3;
}


void Ghost::Unactive()
{
	Enemy::Unactive();
}

void Ghost::ProcessAABBCollision(LPGAMEOBJECT o)
{
	if (dynamic_cast<Simon*>(o))
	{
		Simon* player = dynamic_cast<Simon*>(o);
		player->TakeHit(2);
	}
}
void Ghost::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (!appear) return;
	Enemy::GetBoundingBox(l, t, r, b);
}