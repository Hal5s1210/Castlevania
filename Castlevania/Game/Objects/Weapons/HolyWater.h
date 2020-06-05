#pragma once

#include "..\Bullet.h"

class HolyWater : public Bullet
{
private:
	bool burning;
	bool startBurn;
	DWORD burnTimeStart;
	DWORD burnTime;

	void ProcessAABBCollision(LPGAMEOBJECT coObject) {}
	void ProcessSweptAABBCollision(LPGAMEOBJECT coObject,
		float min_tx, float min_ty, float nx, float ny,
		float& dx, float& dy);

public:
	HolyWater(LPGAMEOBJECT shooter, LPGAMEOBJECT target = NULL) :Bullet(shooter, target) {}

	Bullet* Clone();
	void Ready(float x, float y, bool flip);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Update(DWORD dt, std::vector<LPGAMEOBJECT>* objects);
	void Render(float x = 0, float y = 0);

};

