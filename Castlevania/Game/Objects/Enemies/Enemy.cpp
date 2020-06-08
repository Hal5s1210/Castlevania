#include "Enemy.h"
#include "..\Effect.h"
#include "..\..\..\Framework\Viewport.h"
#include "..\..\Board.h"

Enemy::Enemy()
{
	invulnerableTime = 300;
}

void Enemy::Update(DWORD dt)
{
	if (!alive || !active || outview) return;

	GameObject::Update(dt);
}

void Enemy::Render(float x, float y)
{
	if (!active) return;
	if (!alive || outview) return;

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
	incell = true;
	outview = false;
	SetPosition(default_x, default_y);
	SetAnimation(0);
	SetFlip(default_flip);
}


void Enemy::Unactive()
{
	active = false;
	alive = false;
	incell = false;
	outview = true;
}

bool Enemy::IsHit()
{
	if (GetTickCount() - invulnerableTimeStart >= invulnerableTime)
	{
		hit = false;
	}
	return hit;
}

void Enemy::TakeDamage(int damage, LPGAMEOBJECT hitter)
{
	if (IsHit()) return;

	invulnerableTimeStart = GetTickCount();
	hit = true;

	Effect::AddHitEffect(hitter, this);
	hp -= damage;

	if (hp <= 0)
	{
		hp = 0;
		alive = false;

		LPSPRITE sprite = currentAnimation->first->GetFrame(currentAnimation->second);
		RECT r = sprite->GetRect();

		Effect::AddDeathEffect(r, x, y);

		Board::GetInstance()->AddScore(score);
	}
}

void Enemy::CheckView()
{
	float cam_x, cam_y;
	int cam_w, cam_h;
	Viewport::GetInstance()->GetSize(cam_w, cam_h);
	Viewport::GetInstance()->GetPosition(cam_x, cam_y);
	if (x < cam_x || x > cam_x + cam_w || y < cam_y || y> cam_y + cam_w)
	{
		outview = true;
	}
}