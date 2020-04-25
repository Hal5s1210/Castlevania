#pragma once
#include "..\..\ID.h"
#include "..\GameObject.h"

class TitleEnter: public GameObject
{
public:
	LPGAMEOBJECT Clone();
	void Render(float x, float y);
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}
};
