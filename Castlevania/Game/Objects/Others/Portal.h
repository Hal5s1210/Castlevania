#pragma once

#include "..\..\ID.h"
#include "..\GameObject.h"

class Portal : public GameObject
{
private:
	int w, h;
	int area = -1;
	int scene = -1;
	float player_x = -1, player_y = -1;

	void ProcessAABBCollision(LPGAMEOBJECT coObject) {}
	void ProcessSweptAABBCollision(LPGAMEOBJECT coObject,
		float min_tx, float min_ty, float nx, float ny,
		float& dx, float& dy) {}

public:
	LPGAMEOBJECT Clone() { return NULL; }
	
	void Active();

	void SetSize(int w, int h) { this->w = w; this->h = h; }

	void SetPlayerPosition(float x, float y) { player_x = x; player_y = y; }

	void SetTargetArea(int i) { area = i; }
	void SetTargetScene(int i) { scene = i; }

	void Render(float x, float y);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

