#pragma once

#include "Weapon.h"

class Boomerang : public Weapon
{
private:
	bool comeback;

public:
	LPGAMEOBJECT Clone();
	void Ready(float x, float y, bool flip);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Update(DWORD dt, std::vector<LPGAMEOBJECT>* objects);
};

