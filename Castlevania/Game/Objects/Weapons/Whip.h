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
	LPGAMEOBJECT Clone() { return NULL; }


	void UseWhip(bool use) { isWhip = use; }
	void SetFlip(bool flip) { this->flip = flip; }
	void SetFrameIndex(int i);
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	void Update(DWORD dt, std::vector<LPGAMEOBJECT>* objects);
	void Render(float x = 0, float y = 0);

};

