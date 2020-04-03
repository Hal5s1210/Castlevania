#pragma once

#include "..\ID.h"
#include "GameObject.h"
#include "Simon.h"
#include "SimpleObject.h"
#include "Others\Block.h"

class Generator
{
public:
	static LPGAMEOBJECT PlayerCreate();
	static LPGAMEOBJECT ObjectCreate(int id);
	static LPGAMEOBJECT EnemyCreate(int id) { return 0; }
};

