#pragma once
#include "..\..\ID.h"
#include "..\GameObject.h"

class TitleEnter: public GameObject
{
private:
	void ProcessCollision(std::vector<LPCOEVENT>* coEventResults,
		float min_tx, float min_ty, float nx, float ny,
		float& dx, float& dy) {}

public:
	LPGAMEOBJECT Clone();
	void Render(float x, float y);
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}
};
