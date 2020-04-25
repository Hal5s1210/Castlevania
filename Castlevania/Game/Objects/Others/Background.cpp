#include "Background.h"

LPGAMEOBJECT Background::Clone()
{
	Background* clone = new Background;
	for (ANIMATION* ani : animations)
	{
		clone->AddAnimation(ani->first->Clone());
	}
	clone->SetAnimation(0);
	return clone;
}


void Background::Render(float x, float y)
{
	currentAnimation->first->Draw(currentAnimation->second, this->x + x, this->y + y);
}
