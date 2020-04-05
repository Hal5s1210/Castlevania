#pragma once

#include "..\GameObject.h"

class Torch : public GameObject
{
public:
	LPGAMEOBJECT Clone();
	void Update(DWORD dt);
	void Render(float x = 0, float y = 0);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

