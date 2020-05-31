#pragma once

#include "Enemy.h"

class BlackKnight : public Enemy
{
private:
	bool stop;
	DWORD startStopTime;
	DWORD stopTime = 1000;
	void ProcessCollision(std::vector<LPCOEVENT>* coEventResults,
		float min_tx, float min_ty, float nx, float ny,
		float& dx, float& dy);

public:
	BlackKnight();
	LPENEMY Clone();
	void Active();
	void Unactive();
	void Update(DWORD dt, std::vector<LPGAMEOBJECT>* objects);
};
