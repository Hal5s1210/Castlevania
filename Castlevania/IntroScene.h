#pragma once

#define INTRO_BG_SPRITE_ID			1000
#define INTRO_BG_ANIMATION_ID		2000

#include "Scene.h" 

class IntroBG;
class IntroSimon;

class IntroScene : public Scene
{
private:
	IntroBG* bg;
	IntroSimon* simon;

public:
	void LoadScene();
	void EndScene();
	void Update(DWORD dt);
	void Render();
	void ButtonDown(int keyCode);
	void ButtonUp(int keyCode);

};

class IntroBG :public GameObject
{
public:
	IntroBG();
	~IntroBG();

	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}
};



