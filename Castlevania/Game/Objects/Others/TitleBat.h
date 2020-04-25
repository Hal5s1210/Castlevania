#pragma once
#include "..\..\ID.h"
#include "..\GameObject.h"

class TitleBat : public GameObject
{
public:
	LPGAMEOBJECT Clone();
	void Render(float x, float y);
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}
};

