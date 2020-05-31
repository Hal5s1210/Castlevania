#pragma once

#include "..\GameObject.h"

class SubWeapon
{
private:
	LPGAMEOBJECT wielder;

	int current;
	int shot;
	int bulletcount;
	int heart;
	bool weaponready;
	DWORD delayTimeStart;
	DWORD delayTime;

public:
	SubWeapon(LPGAMEOBJECT wielder);

	bool IsUsable();
	bool IsReady() { return weaponready; }

	void Count(int i) { bulletcount += i; }
	void SetWeapon(int weapon, int shot, int heart);
	void AddWeapon(bool flip, float x, float y);
	void Active();
};

