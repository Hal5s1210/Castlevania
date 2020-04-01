#pragma once

#include "Weapon.h"

class Whip : public Weapon
{
public:
	Whip();
	void SetFrameIndex(int i);
	void Render(float x = 0, float y = 0, bool flip = false);
	void GetBoundingBox(float& l, float& t, float& r, float& b);

};

