#pragma once

#define INTRO_BAT_TEX_ID			2

#define INTRO_BAT_ANIMATION			0

#include "..\..\Framework\GameObject.h"

class IntroBat : public GameObject
{
public:
	IntroBat();
	~IntroBat();

	void Update(DWORD dt);
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}
};

