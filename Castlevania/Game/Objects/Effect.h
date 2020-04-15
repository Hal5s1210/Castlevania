#pragma once

#include "GameObject.h"

class Effect;
typedef Effect* LPEFFECT;

class Effect : public GameObject
{
private:
	bool done;

public:
	bool IsDone() { return done; }
	LPEFFECT Clone();
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}
	void Render(float x, float y);
};


