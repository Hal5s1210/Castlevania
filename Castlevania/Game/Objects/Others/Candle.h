#pragma once

#include "..\GameObject.h"

class Candle : public GameObject
{
private:
	int w, h;
	int hp;
	bool hit;
	bool alive;
	DWORD invulnerableTime;
	DWORD invulnerableTimeStart;
	int item;

	void InitSize();

public:
	Candle();

	void HoldItem(int id) { item = id; }

	bool IsHitted();
	bool IsAlive() { return alive; }
	void TakeDamage(int damage, LPGAMEOBJECT hitter);

	LPGAMEOBJECT Clone();


	void Update(DWORD dt);
	void Render(float x = 0, float y = 0);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

