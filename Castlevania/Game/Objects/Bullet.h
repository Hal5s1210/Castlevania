#pragma once
#include "GameObject.h"

class Bullet : public GameObject
{
protected:
	int damage;
	bool hit;
	bool outview;
	LPGAMEOBJECT shooter;
	LPGAMEOBJECT target;

public:
	Bullet(LPGAMEOBJECT shooter, LPGAMEOBJECT target = NULL);

	virtual Bullet* Clone() = 0;

	void SetShooter(LPGAMEOBJECT o) { shooter = o; }
	void SetTarget(LPGAMEOBJECT o) { target = o; }

	LPGAMEOBJECT GetShooter() { return shooter; }
	LPGAMEOBJECT GetTatget() { return target; }

	bool IsOutOfView() { return outview; }
	bool IsHitSomething() { return hit; }

	virtual void Ready(float x, float y, bool flip) = 0;

	void Render(float x, float y);
	virtual void Update(DWORD dt, std::vector<LPGAMEOBJECT>* objects) = 0;
};

