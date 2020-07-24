#pragma once

#include "Boss.h"

class PhantomBat: public Boss
{
private:
	bool awake;
	bool flying;
	bool attack;

	DWORD readytime;
	DWORD readytimestart;

	std::vector<std::pair<float, float>> positions;
	float pos_x, pos_y;
	int pos;

	DWORD movetime;
	DWORD movetimestart;

	float atk_start_x, atk_start_y;
	float atk_end_x, atk_end_y;
	DWORD attacktime;
	DWORD attacktimestart;

	bool reach_des;
	float des_x, des_y;

	void ProcessAABBCollision(LPGAMEOBJECT coObject);
	void ProcessSweptAABBCollision(LPGAMEOBJECT coObject,
		float min_tx, float min_ty, float nx, float ny,
		float& dx, float& dy) {}

	void GoTo(float desx, float desy);
	void GoInParabola(float desx, float desy);

public:
	PhantomBat();
	void Active();
	void Unactive();
	Enemy* Clone();
	void Brain(DWORD dt);
	void Render(float x, float y);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

