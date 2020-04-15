#pragma once

#include "GameObject.h"

class Item;
typedef Item* LPITEM;

class Item : public GameObject
{
public:
	enum eItem
	{
		Whip,
		Dagger,
		Axe,
		Boomerang,
		StopWatch,
		HolyWater,
		Money100,
		Money400,
		Money700,
		Money1000,
		Money,
		SmallHeart,
		BigHeart,
		DoubleShot,
		TripleShot,
	};

private:
	eItem type;
	bool claimed;
	bool timeOut;
	DWORD timerStart;
	DWORD timeLimit;

public:
	Item();

	void SetType(int type);
	eItem GetType() { return type; }

	bool IsClaimed() { return claimed; }
	bool IsTimeOut() { return timeOut; }

	void Claim() { claimed = true; }

	LPITEM Clone();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Update(DWORD dt, std::vector<LPGAMEOBJECT>* objects);
	void Render(float x, float y);
};

