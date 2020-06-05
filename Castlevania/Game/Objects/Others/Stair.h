#pragma once

#include "..\GameObject.h"

class Stair : public GameObject
{
private:
	int direction_x, direction_y;

	void ProcessAABBCollision(LPGAMEOBJECT coObject) {}
	void ProcessSweptAABBCollision(LPGAMEOBJECT coObject,
		float min_tx, float min_ty, float nx, float ny,
		float& dx, float& dy) {}

public:
	LPGAMEOBJECT Clone() { return NULL; }

	void Update(DWORD dt);

	void SetDirection(int x, int y) { direction_x = x; direction_y = y; }
	void GetDirection(int& x, int& y) { x = direction_x; y = direction_y; }

	void Render(float x, float y);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

