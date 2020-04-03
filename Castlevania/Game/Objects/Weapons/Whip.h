#pragma once

#include "..\..\ID.h"
#include "..\GameObject.h"

class Whip : public GameObject
{
private:
	int index;
	int level;
	bool isWhip;
public:
	Whip();
	void UseWhip(bool use) { isWhip = use; }
	void SetFrameIndex(int i);
	void Render(float x = 0, float y = 0) {}
	void Render(float x = 0, float y = 0, bool flip = false);
	void GetBoundingBox(float& l, float& t, float& r, float& b);

};

