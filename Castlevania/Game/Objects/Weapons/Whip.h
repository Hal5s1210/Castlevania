#pragma once

#include "..\..\ID.h"
#include "..\GameObject.h"

class Whip : public GameObject
{
private:
	int index;
	int level;
	bool isWhip;
	int damage;

	void ProcessCollision(std::vector<LPCOEVENT>* coEventResults,
		float min_tx, float min_ty, float nx, float ny,
		float& dx, float& dy) {}

public:
	Whip();

	void SetLevel(int lv) { level = lv; if (lv > 1) damage = 2; else damage = 1; }

	LPGAMEOBJECT Clone() { return NULL; }

	void UseWhip(bool use) { isWhip = use; }

	void SetFrameIndex(int i);
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	void Update(DWORD dt, std::vector<LPGAMEOBJECT>* objects);
	void Render(float x = 0, float y = 0);

};

