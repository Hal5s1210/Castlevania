#pragma once

#include "Enemy.h"

class Ghost : public Enemy
{
private:
	bool appear;
	void ProcessCollision(std::vector<LPCOEVENT>* coEventResults,
		float min_tx, float min_ty, float nx, float ny,
		float& dx, float& dy) {}

public:
	LPENEMY Clone();
	void Active();
	void Unactive();
	void Update(DWORD dt, std::vector<LPGAMEOBJECT>* objects, Simon* simon);
	void Render(float x, float y);
};