#pragma once

#ifndef SIMON_ANI
#define IDLE						0
#define WALK						1
#define CROUNCH						2
#define ATTACK_1					3
#define ATTACK_2					4
#define HITED						5
#define DEAD						6
#define STAIR_UP					7
#define STAIR_DOWN					8
#define STAIR_UP_ATTACK				9
#define STAIR_DOWN_ATTACK			10
#define UPGRADE						11
#endif // !SIMON_ANI

#define SIMON_SPEED					0.05f
#define JUMP_FORCE					-0.2f;

#include "..\ID.h"
#include "GameObject.h"
#include "Weapons\Whip.h"
#include "Weapons\SubWeapon.h"
#include "Others\Stair.h"

class Simon : public GameObject
{
public:
	enum eState
	{
		Idle,
		WalkL,
		WalkR,
		Crouch,
		Attack,
		SubAttack,
		Jump,
		OnAir,
		Hitted,
		Dead,
		StairUp,
		StairDown,
		Upgrade
	};

private:
	bool input;
	float default_x, default_y;
	bool default_flip;

	bool crouch;
	bool attack;
	bool on_air;
	bool falling;
	int fallcount;

	bool on_moving_block;
	float block_vx;

	bool jump;
	DWORD jumptime;
	DWORD jumpstarttime;
	float speed_before_jump;

	bool upgrade;

	bool auto_pilot;
	bool reach_dest;
	float auto_dest_x, auto_dest_y;
	int auto_dir_x, auto_dir_y;

	int stair_dir_x, stair_dir_y;
	float stair_x, stair_y;

	bool on_stair;
	bool use_stair;
	bool step;
	bool step_done;
	bool change_dir;

	bool hit;
	bool dead;
	bool invulnerable;
	bool chopchop;

	bool invisible;
	DWORD invisibletimestart;
	DWORD invisibletime;

	bool hit_door;

	DWORD hittimestart;
	DWORD hittime;
	DWORD invulnerabletimestart;
	DWORD invulnerabletime;

	Whip* whip;
	SubWeapon* subweapon;

	eState state;

	void NoCollision();
	void ProcessAABBCollision(LPGAMEOBJECT coObject);
	void ProcessSweptAABBCollision(LPGAMEOBJECT coObject,
		float min_tx, float min_ty, float nx, float ny,
		float& dx, float& dy);

	void ProcessState();
	void AutoMove(std::vector<LPGAMEOBJECT>* objects);
	void CheckInCamera();


public:
	Simon();
	~Simon();

	LPGAMEOBJECT Clone() { return NULL; }

	Whip* GetWhip() { return whip; }
	SubWeapon* GetSubWeapon() { return subweapon; }
	void UpgradeWhip() { SetState(Simon::Upgrade); ProcessState(); }
	bool IsInputEnable() { return input; }
	void GainControl();
	void SetState(eState state, bool priority = false);
	void SetDefault(float x, float y, bool flip) { default_x = x; default_y = y; default_flip = flip; }
	void HitStair(Stair* stair);
	void TakeHit(int damage);
	void Reset();
	void GoToX(float x);
	bool IsHitDoor() { return hit_door; }
	bool IsReachAutoDest() { return reach_dest; }
	bool IsInvisible() { return invisible; }
	void GoInvisible();

	void Update(DWORD dt, std::vector<LPGAMEOBJECT>* objects);
	void Render(float x = 0, float y = 0);
	void GetBoundingBox(float& l, float& t, float& r, float& b);

};

