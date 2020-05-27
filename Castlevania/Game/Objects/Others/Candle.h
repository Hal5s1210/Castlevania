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
	void ProcessCollision(std::vector<LPCOEVENT>* coEventResults,
		float min_tx, float min_ty, float nx, float ny,
		float& dx, float& dy) {}

public:
	Candle();

	void HoldItem(int id) { item = id; }

	bool IsHit();
	bool IsAlive() { return alive; }
	void TakeDamage(int damage, LPGAMEOBJECT hitter);

	LPGAMEOBJECT Clone();


	void Update(DWORD dt);
	void Render(float x = 0, float y = 0);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

