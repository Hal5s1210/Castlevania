#include "SimpleObject.h"

void SimpleObject::Update(DWORD dt)
{
	GameObject::Update(dt);
	x += dx;
	y += dy;
}

void SimpleObject::Render(float x, float y)
{
	currentAnimation->Draw(this->x + x, this->y + y);
}