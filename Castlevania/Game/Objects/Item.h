#pragma once

#include "GameObject.h"

class Item;
typedef Item* LPITEM;

class Item : public GameObject
{
public:
	enum eItem
	{
		Unknown,
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
		SmallHeart,
		BigHeart,
		Crown,
		Chest,
		IslandHead,
		LifeUp,
		Pork,
		Cross,
		DoubleShot,
		TripleShot,
		Crystall,
		Invisible
	};

private:
	eItem type;
	bool claimed;
	bool timeOut;
	DWORD timerStart;
	DWORD timeLimit;

	void ProcessAABBCollision(LPGAMEOBJECT coObject) {}
	void ProcessSweptAABBCollision(LPGAMEOBJECT coObject,
		float min_tx, float min_ty, float nx, float ny,
		float& dx, float& dy);

public:
	Item();

	void SetType(int type);
	eItem GetType() { return type; }

	bool IsClaimed() { return claimed; }
	bool IsTimeOut() { return timeOut; }

	void Claim() { claimed = true; }
	void RunEffect(int id);

	static void AddItem(int id, RECT r, float x, float y);

	LPITEM Clone();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Update(DWORD dt, std::vector<LPGAMEOBJECT>* objects);
	void Render(float x, float y);
};

