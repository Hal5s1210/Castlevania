#pragma once

#define TITLE_BG_TEX_ID				1
#define TITLE_BG_TEX_DIR			L"Resources\\Textures\\TitleBG.png"

#define TITLE_BAT_TEX_ID			2
#define TITLE_BAT_TEX_DIR			L"Resources\\Textures\\TitleBat.png"

#define TITLE_TEXT_TEX_ID			3
#define TITLE_TEXT_TEX_DIR			L"Resources\\Textures\\TitleText.png"

#define TITLE_BG_ANIMATION			0

#define TITLE_BAT_ANIMATION_1		0
#define TITLE_BAT_ANIMATION_2		1

#define TITLE_TEXT_ANIMATION_1		0
#define TITLE_TEXT_ANIMATION_2		1

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

	void Enter();

};

class TitleKeyHandler : public KeyEventHandler
{
public:
	void KeyState(BYTE* state);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
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

	void Update(DWORD dt);
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

