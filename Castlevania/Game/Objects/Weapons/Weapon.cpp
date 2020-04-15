#include "Weapon.h"

Weapon::Weapon()
{
	damage = 2;
	hitted = false;
	outView = false;
}

void Weapon::Render(float x, float y)
{
	currentAnimation->first->Draw(currentAnimation->second, this->x + x, this->y + y, 255, flip);
}
