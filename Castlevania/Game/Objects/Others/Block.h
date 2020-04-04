#pragma once

#include "..\..\ID.h"
#include "..\GameObject.h"

class Block : public GameObject
{
private:
	int w = 16, h = 16;
public:
	void SetSize(int w, int h) { this->w = w; this->h = h; }
	void Render(float x, float y) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

