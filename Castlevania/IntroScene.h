#pragma once

#define INTRO_BG_SPRITE_ID			1000
#define INTRO_BG_ANIMATION_ID		2000

#define INTRO_BAT_SPRITE_1_ID		1100
#define INTRO_BAT_SPRITE_2_ID		1101
#define INTRO_BAT_ANIMATION_ID		2100

#define INTRO_CLOUD_SPRITE_ID		1200
#define INTRO_CLOUD_ANIMATION_ID	2200


#define INTRO_SIMON_SPRITE_1_ID		1300
#define INTRO_SIMON_SPRITE_2_ID		1301
#define INTRO_SIMON_SPRITE_3_ID		1302
#define INTRO_SIMON_SPRITE_4_ID		1303
#define INTRO_SIMON_ANIMATION_1_ID	2300
#define INTRO_SIMON_ANIMATION_2_ID	2301

#define INTRO_SONG_ID				1000
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
	void ButtonDown(int keyCode) {}
	void ButtonUp(int keyCode) {}

};

class IntroBG :public GameObject
{
public:
	IntroBG();
	~IntroBG();

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

