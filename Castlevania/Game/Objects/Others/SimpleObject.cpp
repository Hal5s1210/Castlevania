#include "SimpleObject.h"

LPGAMEOBJECT SimpleObject::Clone()
{
	SimpleObject* clone = new SimpleObject;
	for (ANIMATION* ani : animations)
	{
		clone->AddAnimation(ani->first->Clone());
	}
	clone->SetAnimation(0);
	clone->SetName(name);
	return clone;
}

void SimpleObject::Update(DWORD dt)
{
	GameObject::Update(dt);
	x += dx;
	y += dy;
}

void SimpleObject::Render(float x, float y)
{
	currentAnimation->first->Draw(currentAnimation->second, this->x + x, this->y + y);
}