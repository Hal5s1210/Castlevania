#pragma once

#include "Enemy.h"

class BlackKnight : public Enemy
{
private:
	bool stop;
	DWORD startStopTime;
	DWORD stopTime = 1000;
	void ProcessAABBCollision(LPGAMEOBJECT coObject);
	void ProcessSweptAABBCollision(LPGAMEOBJECT coObject,
		float min_tx, float min_ty, float nx, float ny,
		float& dx, float& dy);

public:
	BlackKnight();
	LPENEMY Clone();
	void Active();
	void Unactive();
	void Update(DWORD dt, std::vector<LPGAMEOBJECT>* objects);
};
