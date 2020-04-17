#pragma once

#include "..\GameObject.h"

class Weapon : public GameObject
{
protected:
	int damage;
	bool hit;
	bool outView;
	LPGAMEOBJECT wielder;

public:
	Weapon(LPGAMEOBJECT wielder);

	bool IsOutOfView() { return outView; }
	bool IsHitSomething() { return hit; }

	virtual void Ready(float x, float y, bool flip) = 0;

	virtual LPGAMEOBJECT Clone() = 0;
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) = 0;
	virtual void Update(DWORD dt, std::vector<LPGAMEOBJECT>* objects) = 0;
	virtual void Render(float x = 0, float y = 0);
};