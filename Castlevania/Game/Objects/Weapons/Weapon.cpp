#include "Weapon.h"

Weapon::Weapon(LPGAMEOBJECT wielder)
{
	this->wielder = wielder;
	damage = 2;
	hit = false;
	outView = false;
}

void Weapon::Render(float x, float y)
{
	currentAnimation->first->Draw(currentAnimation->second, this->x + x, this->y + y, 255, flip);
}
