#pragma once

#include "..\GameObject.h"

class SimpleObject : public GameObject
{
private:
	std::string name;
	void ProcessAABBCollision(LPGAMEOBJECT coObject) {}
	void ProcessSweptAABBCollision(LPGAMEOBJECT coObject,
		float min_tx, float min_ty, float nx, float ny,
		float& dx, float& dy) {}
public:
	void SetName(std::string name) { this->name = name; }
	std::string GetName() { return name; }
	LPGAMEOBJECT Clone();
	void Update(DWORD dt);
	void Render(float x, float y);
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}
};


