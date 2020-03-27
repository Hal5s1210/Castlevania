#pragma once

#define INTRO_CLOUD_TEX_ID			3

#define INTRO_CLOUD_ANIMATION		0

#include "..\..\Framework\GameObject.h"

class IntroCloud : public GameObject
{
public:
	IntroCloud();
	~IntroCloud();

	void Update(DWORD dt);
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}
};

