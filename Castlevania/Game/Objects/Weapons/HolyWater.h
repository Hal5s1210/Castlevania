#pragma once

#include "Weapon.h"

class HolyWater : public Weapon
{
private:
	bool burning;
	bool startBurn;
	DWORD burnTimeStart;
	DWORD burnTime;

public:
	HolyWater(LPGAMEOBJECT wielder) :Weapon(wielder) {}

	LPGAMEOBJECT Clone();
	void Ready(float x, float y, bool flip);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Update(DWORD dt, std::vector<LPGAMEOBJECT>* objects);
	void Render(float x = 0, float y = 0);

};

