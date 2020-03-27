#pragma once

#define INTRO_SIMON_ANIMATION_1		0
#define INTRO_SIMON_ANIMATION_2		1

#define INTRO_SONG_ID				1

#include "..\..\Framework\Scene.h" 

class IntroScene : public Scene
{
private:
	DWORD time;

public:
	void LoadScene();
	void EndScene();
	void UpdateScene(DWORD dt);
	void RenderScene();

};

