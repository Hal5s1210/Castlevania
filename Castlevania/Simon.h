#pragma once

#define SIMON_TEX_ID				0000
#define SIMON_TEX_DIR				L"Resources\\Textures\\Simon.png"

#define SIMON_IDLE_ANIMATION		0
#define SIMON_WALK_ANIMATION		1

#define SIMON_STATE_IDLE			0
#define SIMON_STATE_WALK_LEFT		1
#define SIMON_STATE_WALK_RIGHT		2

#include "GameObject.h"

class Simon : public GameObject
{
public:
	Simon();
	~Simon();

	void SetState(int state);

	void Update(DWORD dt, std::vector<LPGAMEOBJECT>* objects);
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);

};

