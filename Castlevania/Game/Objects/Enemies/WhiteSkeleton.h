#pragma once

#include "Enemy.h"

class WhiteSkeleton : public Enemy
{
private:
	int state;
	bool jump;
	float limitL, limitR;
	DWORD startstatetime;
	DWORD timeeachstate;
	void ProcessCollision(std::vector<LPCOEVENT>* coEventResults,
		float min_tx, float min_ty, float nx, float ny,
		float& dx, float& dy);

public:
	WhiteSkeleton();
	LPENEMY Clone();
	void Active();
	void Unactive();
	void Update(DWORD dt, std::vector<LPGAMEOBJECT>* objects);
};
