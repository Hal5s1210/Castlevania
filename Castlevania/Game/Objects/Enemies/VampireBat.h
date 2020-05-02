#pragma once

#include "Enemy.h"

class VampireBat : public Enemy
{
private:
	void ProcessCollision(std::vector<LPCOEVENT>* coEventResults,
		float min_tx, float min_ty, float nx, float ny,
		float& dx, float& dy) {}

public:
	LPENEMY Clone();
};

