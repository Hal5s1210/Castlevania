#pragma once

#define SIMON_TEX_ID				0000
#define SIMON_TEX_DIR				L"Resources\\Textures\\Simon.png"

#define SIMON_IDLE_ANIMATION		0
#define SIMON_WALK_ANIMATION		1
#define SIMON_CROUNCH_ANIMATION		2
#define SIMON_ATTACK_1_ANIMATION	3
#define SIMON_ATTACK_2_ANIMATION	4
#define SIMON_HITED_ANIMATION		5
#define SIMON_DEAD_ANIMATION		6

#define SIMON_SPEED					0.1f
#define JUMP_FORCE					-0.5f;
#define GRAVITY						0.002f;

#include "GameObject.h"

class Simon : public GameObject
{
private:
	bool attack;
	bool crounch;
	bool jump;
	bool onground;

public:
	Simon();
	~Simon();

	void GoIdle();
	void GoLeft(bool active);
	void GoRight(bool active);
	void Crounch(bool active);
	void Jump();
	void Attack();

	void Update(DWORD dt, std::vector<LPGAMEOBJECT>* objects);
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);

};

