#include "TitleBat.h"

LPGAMEOBJECT TitleBat::Clone()
{
	TitleBat* clone = new TitleBat;
	for (ANIMATION* ani : animations)
	{
		clone->AddAnimation(ani->first->Clone());
	}
	clone->SetAnimation(0);
	return clone;
}

void TitleBat::Render(float x, float y)
{
	currentAnimation->first->Draw(currentAnimation->second, this->x + x, this->y + y);

	if (currentAnimation->first->IsFrameReset())
	{
		SetAnimation(1);
	}
}