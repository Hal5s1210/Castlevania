#pragma once
#include "..\..\ID.h"
#include "..\GameObject.h"

class Door : public GameObject
{
private:
	int state;

	bool active;
	bool open;
	bool close;
	bool player_move;

	void ProcessAABBCollision(LPGAMEOBJECT coObject) {}
	void ProcessSweptAABBCollision(LPGAMEOBJECT coObject,
		float min_tx, float min_ty, float nx, float ny,
		float& dx, float& dy) {}

public:
	Door();

	void Active();

	LPGAMEOBJECT Clone();
	void Update(DWORD dt);
	void Render(float x, float y);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};
