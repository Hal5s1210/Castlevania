#pragma once

#include "..\Enemy.h"

class Boss : public Enemy
{
public:
	void TakeDamage(int damage, LPGAMEOBJECT hitter);
};

