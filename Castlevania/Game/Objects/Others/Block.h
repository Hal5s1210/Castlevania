#pragma once

#include "..\..\ID.h"
#include "..\GameObject.h"

class Block : public GameObject
{
public:
	LPGAMEOBJECT Clone() { return NULL; }
	void Render(float x, float y);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

