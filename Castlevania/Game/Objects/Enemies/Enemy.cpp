#include "Enemy.h"

void Enemy::Render(float x, float y)
{
	if (!alive) return;
	currentAnimation->first->Draw(currentAnimation->second, this->x + x, this->y + y);

	if (Debug::IsEnable())
	{
		float l, t, r, b;
		GetBoundingBox(l, t, r, b);
		Debug::RenderBoundBox(x, y, l, t, r, b);
	}
}

void Enemy::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	LPSPRITE sprite = currentAnimation->first->GetFrame(currentAnimation->second);
	RECT rect = sprite->GetRect();

	l = x;
	t = y;
	r = l + (rect.right - rect.left);
	b = t + (rect.bottom - rect.top);
}

void Enemy::Active()
{
	alive = true;
	SetPosition(default_x, default_y);
	SetAnimation(0);
	SetFlip(default_flip);
}