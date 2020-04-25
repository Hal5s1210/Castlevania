#include "TitleEnter.h"

LPGAMEOBJECT TitleEnter::Clone()
{
	TitleEnter* clone = new TitleEnter;
	for (ANIMATION* ani : animations)
	{
		clone->AddAnimation(ani->first->Clone());
	}
	clone->SetAnimation(0);
	return clone;
}


void TitleEnter::Render(float x, float y)
{
	currentAnimation->first->Draw(currentAnimation->second, this->x + x, this->y + y);
}