#pragma once

#include "GameObject.h"

class Effect;
typedef Effect* LPEFFECT;

class Effect : public GameObject
{
private:
	bool done;
	bool oneTimeEffect = true;
	bool gravity;
	bool outView;
	DWORD startTime;
	DWORD time;

	void ProcessCollision(std::vector<LPCOEVENT>* coEventResults,
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
};


