#include "PhantomBat.h"
#include "..\..\..\Scenes\Scene.h"

PhantomBat::PhantomBat()
{
	score = 10000;
	reach_des = true;
}
Enemy* PhantomBat::Clone()
{
	PhantomBat* clone = new PhantomBat;
	for (ANIMATION* ani : animations)
	{
		clone->AddAnimation(ani->first->Clone());
	}
	clone->SetAnimation(0);
	return clone;
}

void PhantomBat::Active()
{
	Enemy::Active();
}

void PhantomBat::Unactive()
{
	Enemy::Unactive();
}

void PhantomBat::Brain(DWORD dt)
{
	Simon* player = Scenes::GetInstance()->GetScene()->GetPlayer();
	float p_x, p_y;
	player->GetPosition(p_x, p_y);

	if (!awake && p_x >= activeL && p_x <= activeR)
	{
		awake = true;
		SetAnimation(1);
	}

	if (awake)
	{
		/*if (reach_des)
		{
			des_x = p_x + (rand() % 240 - 120);
			des_y = p_y - 60 - (rand() % 60);

			GoTo(des_x, des_y);
		}

		x += vx * dt;
		y += vy * dt;*/
	}
	
}

void PhantomBat::GoTo(float desx, float desy)
{
	vx = desx > x ? 0.1 : desx < x ? -0.1 : 0;
	vy = desy > y ? -0.1 : desy < y ? 0.1 : 0;

	reach_des = false;
}

void PhantomBat::Render(float x, float y)
{
	if (!active) return;
	if (!alive || outview) return;

	float X, Y;
	LPSPRITE sprite = currentAnimation->first->GetFrame(currentAnimation->second);
	RECT rect = sprite->GetRect();
	int w = rect.right - rect.left;
	X = this->x + 8 - w / 2;
	Y = this->y;

	currentAnimation->first->Draw(currentAnimation->second, X + x, Y + y, 255, flip);

	if (Debug::IsEnable())
	{
		float l, t, r, b;
		GetBoundingBox(l, t, r, b);
		Debug::RenderBoundBox(x, y, l, t, r, b);
	}
}

void PhantomBat::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (!awake) return;

	LPSPRITE sprite = currentAnimation->first->GetFrame(currentAnimation->second);
	RECT rect = sprite->GetRect();
	int w = rect.right - rect.left;
	int h = rect.bottom - rect.top;

	l = x + 8 - w / 2;
	r = l + w;
	t = y;
	b = t + h;
}