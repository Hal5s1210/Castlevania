#pragma once

#include "..\..\ID.h"
#include "..\GameObject.h"

class Portal : public GameObject
{
private:
	int w, h;
	int area;
	int scene;
	float player_x, player_y;
	bool onetime;
	bool active;

	void ProcessAABBCollision(LPGAMEOBJECT coObject) {}
	void ProcessSweptAABBCollision(LPGAMEOBJECT coObject,
		float min_tx, float min_ty, float nx, float ny,
		float& dx, float& dy) {}

public:
	Portal();

	LPGAMEOBJECT Clone() { return NULL; }
	
	bool IsActive() { return active; }
	void Active();

	void IsOneTimeUse(bool one) { onetime = one; }

	void SetSize(int w, int h) { this->w = w; this->h = h; }

	void SetPlayerPosition(float x, float y) { player_x = x; player_y = y; }

	void SetTargetArea(int i) { area = i; }
	void SetTargetScene(int i) { scene = i; }

	void Reset();
	
	void Render(float x, float y);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

