#pragma once

#include "Enemy.h"

class Hunchback : public Enemy
{
private:
	bool attack;
	int jump;
	bool land;
	DWORD timebetweenjumps;
	DWORD lastjump;
	void ProcessCollision(std::vector<LPCOEVENT>* coEventResults,
		float min_tx, float min_ty, float nx, float ny,
		float& dx, float& dy);

public:
	Hunchback();
	LPENEMY Clone();
	void Active();
	void Unactive();
	void Update(DWORD dt, std::vector<LPGAMEOBJECT>* objects);
};

