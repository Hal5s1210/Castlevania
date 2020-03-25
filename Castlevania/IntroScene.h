#pragma once

#define INTRO_BG_TEX_ID				1
#define INTRO_BG_TEX_DIR			L"Resources\\Textures\\IntroBG.png"

#define INTRO_BAT_TEX_ID			2
#define INTRO_BAT_TEX_DIR			L"Resources\\Textures\\IntroBat.png"

#define INTRO_CLOUD_TEX_ID			3
#define INTRO_CLOUD_TEX_DIR			L"Resources\\Textures\\IntroCloud.png"

#define INTRO_BG_ANIMATION			0

#define INTRO_BAT_ANIMATION			0

#define INTRO_CLOUD_ANIMATION		0

#define INTRO_SIMON_ANIMATION_1		0
#define INTRO_SIMON_ANIMATION_2		1


#define INTRO_SONG_ID				0
#define INTRO_SONG_DIR				"Resources\\Sounds\\01. Introduction (Castle Gate).wav"


#include "Scene.h" 

class IntroBG;
class IntroBat;
class IntroCloud;
class IntroSimon;

class IntroScene : public Scene
{
private:
	IntroBG* bg;
	IntroBat* bat1;
	IntroBat* bat2;
	IntroCloud* cloud;
	IntroSimon* simon;
	DWORD time;

public:
	void LoadScene();
	void EndScene();
	void Update(DWORD dt);
	void Render();

};


class IntroBG :public GameObject
{
public:
	IntroBG();
	~IntroBG();

	void SetState(int state) { currentAnimation = state; }
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}
};


class IntroBat : public GameObject
{
public:
	IntroBat();
	~IntroBat();

	void Update(DWORD dt);
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}
};


class IntroCloud : public GameObject
{
public:
	IntroCloud();
	~IntroCloud();

	void Update(DWORD dt);
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}
};


class IntroSimon : public GameObject
{
public:
	IntroSimon();
	~IntroSimon();

	void Update(DWORD dt);
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}

};

