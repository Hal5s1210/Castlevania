#pragma once

#include "..\GameObject.h"

class Enemy : public GameObject
{
private:
	bool alive;
	int hp;
	int score;
	float default_x, default_y;
	bool default_flip;

public:
	bool IsAlive() { return alive; }
	void Active();

	void SetDefaultFlip(bool flip) { default_flip = flip; }
	void SetDefaultPosition(float x, float y) { default_x = x; default_y = y; }

	void GetDefaultPosition(float& x, float& y) { x = default_x; y = default_y; }

	virtual Enemy* Clone() = 0;
	void Render(float x, float y);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};
typedef Enemy* LPENEMY;

