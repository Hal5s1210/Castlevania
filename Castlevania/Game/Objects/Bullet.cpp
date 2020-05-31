#include "Bullet.h"
#include "Simon.h"

Bullet::Bullet(LPGAMEOBJECT shooter, LPGAMEOBJECT target)
{
	this->shooter = shooter;
	this->target = target;
	damage = 2;
	hit = false;
	outview = false;
}

void Bullet::Render(float x, float y)
{
	currentAnimation->first->Draw(currentAnimation->second, this->x + x, this->y + y, 255, flip);

	if (Debug::IsEnable())
	{
		float l, t, r, b;
		GetBoundingBox(l, t, r, b);
		Debug::RenderBoundBox(x, y, l, t, r, b);
	}
}
