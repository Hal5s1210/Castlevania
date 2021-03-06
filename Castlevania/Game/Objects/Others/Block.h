#pragma once

#include "..\..\ID.h"
#include "..\GameObject.h"

class Block : public GameObject
{
private:
	void ProcessAABBCollision(LPGAMEOBJECT coObject) {}
	void ProcessSweptAABBCollision(LPGAMEOBJECT coObject,
		float min_tx, float min_ty, float nx, float ny,
		float& dx, float& dy) {}

public:
	LPGAMEOBJECT Clone() { return NULL; }
	void Render(float x, float y);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

