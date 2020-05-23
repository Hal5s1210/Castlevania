#pragma once

#include "Enemy.h"

class Hunchback : public Enemy
{
private:
	bool jump;
	bool leap;
	void ProcessCollision(std::vector<LPCOEVENT>* coEventResults,
		float min_tx, float min_ty, float nx, float ny,
		float& dx, float& dy);

public:
	LPENEMY Clone();
	void Active();
	void Unactive();
	void Update(DWORD dt, std::vector<LPGAMEOBJECT>* objects, Simon* simon);
};

