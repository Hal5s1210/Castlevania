#pragma once

#include "GameObject.h"

class Effect;
typedef Effect* LPEFFECT;

class Effect : public GameObject
{
private:
	bool done;
	DWORD startTime;
	DWORD time;

public:
	LPEFFECT Clone();
	bool IsDone() { return done; }
	void SetTime(int n) { time = n; startTime = GetTickCount(); }
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}
	void Render(float x, float y);
};


