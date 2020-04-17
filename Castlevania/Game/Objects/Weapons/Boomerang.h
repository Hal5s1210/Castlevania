#pragma once

#include "Weapon.h"

class Boomerang : public Weapon
{
private:
	float returnPoint;
	bool comeback;
	bool back;

public:
	Boomerang(LPGAMEOBJECT wielder) :Weapon(wielder) {}

	LPGAMEOBJECT Clone();
	void Ready(float x, float y, bool flip);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Update(DWORD dt, std::vector<LPGAMEOBJECT>* objects);
};
