#pragma once

#include "..\..\ID.h"
#include "..\GameObject.h"

class IntroBat : public GameObject
{
public:
	IntroBat();

	void Update(DWORD dt);
	void Render(float x = 0, float y = 0);
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}
};
