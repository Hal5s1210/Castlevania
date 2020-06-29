#pragma once

#include "GameObject.h"

class Effect;
typedef Effect* LPEFFECT;

class Effect : public GameObject
{
private:
	static bool flash;
	static int flashcount;

	bool done;
	bool oneTimeEffect = true;
	bool gravity;
	bool outView;
	DWORD startTime;
	DWORD time;

	void ProcessAABBCollision(LPGAMEOBJECT coObject) {}
	void ProcessSweptAABBCollision(LPGAMEOBJECT coObject,
		float min_tx, float min_ty, float nx, float ny,
		float& dx, float& dy) {}

public:
	LPEFFECT Clone();
	bool IsDone() { return done; }
	void OnetimeEffect(bool onetime) { oneTimeEffect = onetime; }
	bool IsOneTimeEffect() { return oneTimeEffect; }
	void SetTime(int n) { time = n; startTime = GetTickCount(); }
	void UseGravity() { gravity = true; }
	bool IsOutOfView() { return outView; }

	void GetBoundingBox(float& l, float& t, float& r, float& b) {}
	void Update(DWORD dt);
	void Render(float x, float y);

	static void AddHitEffect(LPGAMEOBJECT hitter, LPGAMEOBJECT obj);
	static void AddDeathEffect(RECT r, float x, float y);
	static void AddBossDeathEffect(RECT r, float x, float y);
	static void AddBreakBlockEffect(RECT r, float x, float y);
	static void RenderBackgroundEffect();
	static void Flash();
};


