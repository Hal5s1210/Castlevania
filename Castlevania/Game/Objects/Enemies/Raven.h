#pragma once

#include "Enemy.h"

class Raven : public Enemy
{
private:
	bool fly;
	bool attack;
	DWORD lastattack;
	DWORD timebetweenattack;
	DWORD startwait;
	DWORD waittime;
	float atk_y;
	void ProcessAABBCollision(LPGAMEOBJECT coObject);
	void ProcessSweptAABBCollision(LPGAMEOBJECT coObject,
		float min_tx, float min_ty, float nx, float ny,
		float& dx, float& dy) {}

public:
	Raven();
	LPENEMY Clone();
	void Active();
	void Unactive();
	void Update(DWORD dt, std::vector<LPGAMEOBJECT>* objects);
};

