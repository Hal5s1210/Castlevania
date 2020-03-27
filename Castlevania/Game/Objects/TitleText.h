#pragma once

#define TITLE_TEXT_TEX_ID			2

#define TITLE_TEXT_ANIMATION_1		0
#define TITLE_TEXT_ANIMATION_2		1

#include "..\..\Framework\GameObject.h"

class TitleText : public GameObject
{
public:
	TitleText();
	~TitleText();

	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}

};

