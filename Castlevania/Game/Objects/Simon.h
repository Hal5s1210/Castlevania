#pragma once

#ifndef SIMON_ANI
#define IDLE						0
#define WALK						1
#define CROUNCH						2
#define ATTACK_1					3
#define ATTACK_2					4
#define HITED						5
#define DEAD						6
#endif // !SIMON_ANI

#define SIMON_SPEED					0.067f
#define JUMP_FORCE					-0.2f;
#define GRAVITY						0.0005f;

#include "..\ID.h"
#include "GameObject.h"
#include "Weapons\Whip.h"
#include "Weapons\SubWeapon.h"
#include "..\..\Dependencies\pugixml\src\pugixml.hpp"

class Simon : public GameObject
{
public:
	enum eState
	{
		Idle,
		WalkL,
		WalkR,
		Crounch,
		Attack,
		SubAttack,
		Jump,
		OnAir,
		Hitted,
		Dead
	};

private:
	DWORD jumpTime;
	DWORD jumpStartTime;

	bool crounch;
	bool attack;
	bool onair;
	bool onstair;
	bool hitted;
	bool dead;

	Whip* whip;
	SubWeapon* subweapon;

	eState state;

	void ProcessState();

public:
	Simon();
	~Simon();

	LPGAMEOBJECT Clone() { return NULL; }

	Whip* GetWhip() { return whip; }
	SubWeapon* GetSubWeapon() { return subweapon; }

	void SetState(eState state);

	void Update(DWORD dt, std::vector<LPGAMEOBJECT>* objects);
	void Render(float x = 0, float y = 0);
	void GetBoundingBox(float& l, float& t, float& r, float& b);

};

