#pragma once

#include "..\ID.h"
#include "GameObject.h"

class TitleBat : public GameObject
{
public:
	TitleBat();

	void Update(DWORD dt);
	void Render(float x = 0, float y = 0);
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}

};
