#pragma once

#include "..\..\ID.h"
#include "..\GameObject.h"

class Portal : public GameObject
{
private:
	int w, h;
	int area = -1;
	int scene = -1;
public:
	LPGAMEOBJECT Clone() { return NULL; }
	
	void Active();

	void SetSize(int w, int h) { this->w = w; this->h = h; }

	void SetTargetArea(int i) { area = i; }
	void SetTargetScene(int i) { scene = i; }

	void Render(float x, float y);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

