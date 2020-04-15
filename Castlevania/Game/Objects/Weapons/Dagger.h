#pragma once

#include "Weapon.h"

class Dagger : public Weapon
{
public:
	LPGAMEOBJECT Clone();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Update(DWORD dt, std::vector<LPGAMEOBJECT>* objects);
};

