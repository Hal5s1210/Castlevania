#pragma once

#define INTRO_BG_TEX_ID				1

#define INTRO_BG_ANIMATION			0

#include "..\..\Framework\GameObject.h"

class IntroBG :public GameObject
{
public:
	IntroBG();
	~IntroBG();

	void SetState(int state) { currentAnimation = state; }
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}
};
