#pragma once

#include "Dagger.h"

class SubWeapon
{
private:
	int current;
	int shot;

	Dagger* dagger;

	std::vector<Weapon*> weapons;

public:
	SubWeapon();

	Dagger* GetDagger() { return dagger; }

	void SetWeapon(int weapon, int shot) { current = weapon; this->shot = shot; }
	void Active(bool flip, float x, float y);
	void Update(DWORD dt, std::vector<LPGAMEOBJECT>* objects);
	void Render(float x, float y);
};

