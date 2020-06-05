#pragma once

#include "Enemy.h"

class Zombie : public Enemy
{
private:
	bool move;
	void ProcessAABBCollision(LPGAMEOBJECT coObject);
	void ProcessSweptAABBCollision(LPGAMEOBJECT coObject,
		float min_tx, float min_ty, float nx, float ny,
		float& dx, float& dy);

public:
	Zombie();
	LPENEMY Clone();
	void Active();
	void Unactive();
	void Update(DWORD dt, std::vector<LPGAMEOBJECT>* objects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};
