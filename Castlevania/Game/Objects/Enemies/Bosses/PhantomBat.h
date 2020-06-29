#pragma once

#include "Boss.h"

class PhantomBat: public Boss
{
private:
	bool awake;

	bool reach_des;
	float des_x, des_y;

	void ProcessAABBCollision(LPGAMEOBJECT coObject) {}
	void ProcessSweptAABBCollision(LPGAMEOBJECT coObject,
		float min_tx, float min_ty, float nx, float ny,
		float& dx, float& dy) {}

	void GoTo(float desx, float desy);

public:
	PhantomBat();
	void Active();
	void Unactive();
	Enemy* Clone();
	void Brain(DWORD dt);
	void Render(float x, float y);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

