#pragma once

#include "Weapon.h"

class Stopwatch
{
private:
	LPGAMEOBJECT wielder;
	int time;

public:
	Stopwatch(LPGAMEOBJECT wielder);
	void Active(int shot);

};

