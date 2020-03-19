#pragma once

#define TITLE_BG_SPRITE_ID				1000
#define TITLE_BG_ANIMATION_ID			2000

#define TITLE_BAT_SPRITE_ID				1100
#define TITLE_BAT_ANIMATION_1_ID		2100
#define TITLE_BAT_ANIMATION_2_ID		2101

#define START_TEXT_SPRITE_1_ID			1200
#define START_TEXT_SPRITE_2_ID			1201
#define START_TEXT_ANIMATION_1_ID		2200
#define START_TEXT_ANIMATION_2_ID		2201

#include "Scene.h" 

class TitleBG;
class TitleBat;
class StartText;

class TitleScene : public Scene
{
private:
	TitleBG* bg;
	TitleBat* bat;
	StartText* text;
	bool enter;
	DWORD time = -1;

public:
	void LoadScene();
	void EndScene();
	void Update(DWORD dt);
	void Render();
	void ButtonDown(int keyCode);
	void ButtonUp(int keyCode);

};


class TitleBG : public GameObject
{
public:
	TitleBG();
	~TitleBG();

	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}

};


class TitleBat : public GameObject
{
public:
	TitleBat();
	~TitleBat();

	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}

};


class StartText : public GameObject
{
public:
	StartText();
	~StartText();

	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}

};

