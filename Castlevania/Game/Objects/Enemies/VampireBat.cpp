#include "VampireBat.h"

LPENEMY VampireBat::Clone()
{
	VampireBat* clone = new VampireBat;
	for (ANIMATION* ani : animations)
	{
		clone->AddAnimation(ani->first->Clone());
	}
	clone->SetAnimation(0);
	return clone;
}