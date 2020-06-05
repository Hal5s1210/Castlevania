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

void Ghost::Update(DWORD dt, std::vector<LPGAMEOBJECT>* objects)
{

	Simon* player = Scenes::GetInstance()->GetScene()->GetPlayer();
	float p_x, p_y;
	player->GetPosition(p_x, p_y);

	if (!alive && hp > 0 && p_x >= activeL && p_x <= activeR)
	{
		alive = true;
	}

	if (!alive || !active || outview) return;

	Enemy::Update(dt);

	if (alive)
	{
		if (p_x < x && flip) flip = false;
		if (p_x > x && !flip) flip = true;

		vx = flip ? 0.04 : -0.04;
		vy = p_y > y ? 0.02 : -0.02;

		GameObject::CheckCollision(objects);

		if (!incell && !outview)
			Enemy::CheckView();
	}

}

void Ghost::Render(float x, float y)
{
	Enemy::Render(x, y);
}


void Ghost::Active()
{
	Enemy::Active();
	alive = false;
	hp = 3;
}


void Ghost::Unactive()
{
	Enemy::Unactive();
}

void Ghost::ProcessSweptAABBCollision(LPGAMEOBJECT o,
	float min_tx, float min_ty, float nx, float ny,
	float& dx, float& dy)
{
	if (dynamic_cast<Simon*>(o))
	{
		Simon* player = dynamic_cast<Simon*>(o);
		player->TakeHit(2);
	}
}

void Ghost::ProcessAABBCollision(LPGAMEOBJECT o)
{
	if (dynamic_cast<Simon*>(o))
	{
		Simon* player = dynamic_cast<Simon*>(o);
		player->TakeHit(2);
	}
}