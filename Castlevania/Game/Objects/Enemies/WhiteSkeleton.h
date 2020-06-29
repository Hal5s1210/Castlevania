#pragma once

#include "Enemy.h"

class WhiteSkeleton : public Enemy
{
private:
	bool start;
	bool moveforward;
	int counttoattack;
	float limitL, limitR;
	DWORD startstatetime;
	DWORD timeeachstate;
	void ProcessAABBCollision(LPGAMEOBJECT coObject);
	void ProcessSweptAABBCollision(LPGAMEOBJECT coObject,
		float min_tx, float min_ty, float nx, float ny,
		float& dx, float& dy);

public:
	WhiteSkeleton();
	LPENEMY Clone();
	void Active();
	void Unactive();
	void Brain(DWORD dt);
};