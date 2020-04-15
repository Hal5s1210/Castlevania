#include "Effect.h"

LPEFFECT Effect::Clone()
{
	Effect* clone = new Effect;
	for (ANIMATION* ani : animations)
	{
		clone->AddAnimation(ani->first->Clone());
	}
	clone->SetAnimation(0);
	return clone;
}

void Effect::Render(float x, float y)
{
	SetAnimation(0);
	currentAnimation->first->Draw(currentAnimation->second, this->x + x, this->y + y);

	if (currentAnimation->first->IsFrameReset())
	{
		done = true;
	}
}

