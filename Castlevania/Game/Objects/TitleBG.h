#pragma once

#define TITLE_BG_TEX_ID			0

#define TITLE_BG_ANIMATION			0

#include "..\..\Framework\GameObject.h"

class TitleBG : public GameObject
{
public:
	TitleBG();
	~TitleBG();

	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}

};
