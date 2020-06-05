#pragma once

#include "..\..\ID.h"
#include "..\GameObject.h"

class MovingBlock : public GameObject
{
private:
	int limit_left, limit_right;
	void ProcessAABBCollision(LPGAMEOBJECT coObject) {}
	void ProcessSweptAABBCollision(LPGAMEOBJECT coObject,
		float min_tx, float min_ty, float nx, float ny,
		float& dx, float& dy) {}

public:
	MovingBlock() {}
	void SetActiveArea(int l, int r) { limit_left = l; limit_right = r; }

	LPGAMEOBJECT Clone();
	void Update(DWORD dt);
	void Render(float x, float y);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

