#pragma once

#include "Enemy.h"

class VampireBat : public Enemy
{
private:
	bool fly;
	float player_pos_y;
	float start_pos_y;
	void ProcessAABBCollision(LPGAMEOBJECT coObject);
	void ProcessSweptAABBCollision(LPGAMEOBJECT coObject,
		float min_tx, float min_ty, float nx, float ny,
		float& dx, float& dy);

public:
	VampireBat();
	LPENEMY Clone();
	void Active();
	void Unactive();
	void Update(DWORD dt, std::vector<LPGAMEOBJECT>* objects);
};

