#pragma once

#define TITLE_BAT_TEX_ID			1

#define TITLE_BAT_ANIMATION_1		0
#define TITLE_BAT_ANIMATION_2		1

#include "..\..\Framework\GameObject.h"

class TitleBat : public GameObject
{
public:
	TitleBat();
	~TitleBat();

	void Update(DWORD dt);
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}

};
