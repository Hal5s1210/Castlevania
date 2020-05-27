#pragma once

#include "..\..\ID.h"
#include "..\GameObject.h"

class BreakableBlock : public GameObject
{
private:
	int hp;
	bool hit;
	bool alive;
	DWORD invulnerableTime;
	DWORD invulnerableTimeStart;
	int item;

	void ProcessCollision(std::vector<LPCOEVENT>* coEventResults,
		float min_tx, float min_ty, float nx, float ny,
		float& dx, float& dy) {}

public:
	BreakableBlock();

	void HoldItem(int id) { item = id; }
	void SetHP(int n) { hp = n; }

	bool IsHit();
	bool IsAlive() { return alive; }
	void TakeDamage();

	LPGAMEOBJECT Clone();
	void Render(float x, float y);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};
