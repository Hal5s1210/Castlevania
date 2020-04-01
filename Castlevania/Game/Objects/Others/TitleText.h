#pragma once

#include "..\..\ID.h"
#include "..\..\Objects\GameObject.h"

class TitleText : public GameObject
{
public:
	TitleText();

	void Render(float x = 0, float y = 0);
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}

};

