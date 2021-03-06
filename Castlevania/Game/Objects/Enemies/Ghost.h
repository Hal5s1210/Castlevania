#pragma once

#include "Enemy.h"

class Ghost : public Enemy
{
private:
	bool appear;
	void ProcessAABBCollision(LPGAMEOBJECT coObject);
	void ProcessSweptAABBCollision(LPGAMEOBJECT coObject,
		float min_tx, float min_ty, float nx, float ny,
		float& dx, float& dy) {}

public:
	Ghost();
	LPENEMY Clone();
	void Active();
	void Unactive();
	void Brain(DWORD dt);
	void Render(float x, float y);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};