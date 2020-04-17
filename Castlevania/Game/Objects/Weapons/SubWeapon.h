#pragma once

#include "Dagger.h"
#include "Axe.h"
#include "Boomerang.h"
#include "HolyWater.h"
#include "Stopwatch.h"

class SubWeapon
{
private:
	LPGAMEOBJECT wielder;

	int current;
	int shot;
	int heart;
	bool weaponready;
	DWORD delayTimeStart;
	DWORD delayTime;


	Dagger* dagger;
	Axe* axe;
	Boomerang* boomerang;
	HolyWater* holywater;
	Stopwatch* stopwatch;

	std::vector<Weapon*> weapons;

public:
	SubWeapon(LPGAMEOBJECT wielder);

	bool IsUsable();
	bool IsReady() { return weaponready; }

	Dagger* GetDagger() { return dagger; }
	Axe* GetAxe() { return axe; }
	Boomerang* GetBoomerang() { return boomerang; }
	HolyWater* GetHolyWater() { return holywater; }

	void SetWeapon(int weapon, int shot, int heart) { current = weapon; this->shot = shot; this->heart = heart; }
	void AddWeapon(bool flip, float x, float y);
	void Active();
	void Update(DWORD dt, std::vector<LPGAMEOBJECT>* objects);
	void Render(float x, float y);
};

