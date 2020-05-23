#include "Enemy.h"
#include "..\Effect.h"

void Enemy::Update(DWORD dt)
{
	if (!alive || !active || !ingrid) return;
	GameObject::Update(dt);
}

void Enemy::Render(float x, float y)
{
	if (!active || !ingrid) return;
	ingrid = false;
	if (!alive) return;

	currentAnimation->first->Draw(currentAnimation->second, this->x + x, this->y + y, 255, flip);


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
	active = true;
	ingrid = true;
	SetPosition(default_x, default_y);
	SetAnimation(0);
	SetFlip(default_flip);
}


void Enemy::Unactive()
{
	active = false;
	alive = false;
	ingrid = false;
}

void Enemy::TakeDamage(int damage, LPGAMEOBJECT hitter)
{
	Effect::AddHitEffect(hitter, this);
	hp = 0;

	if (hp <= 0)
	{
		hp = 0;
		alive = false;

		LPSPRITE sprite = currentAnimation->first->GetFrame(currentAnimation->second);
		RECT r = sprite->GetRect();

		Effect::AddDeathEffect(r, x, y);
	}
}