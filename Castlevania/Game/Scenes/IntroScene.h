#pragma once

#include "Scene.h"

class IntroSceneKeyHandler : public KeyEventHandler
{
	LPSCENE scene;
public:
	IntroSceneKeyHandler(LPSCENE s) :scene(s) {}

	void KeyState(BYTE* state) {}
	void OnKeyDown(int KeyCode) {}
	void OnKeyUp(int KeyCode) {}
};


class IntroScene : public Scene
{
private:
	DWORD scenestart;
	DWORD scenetime;

public:
	IntroScene(float x, float y, std::wstring filepath) : Scene(x, y, filepath)
	{
		keyhandler = new IntroSceneKeyHandler(this);
		scenetime = 7000;
	}

	void Load();
	void Unload();
	void Update(DWORD dt);
	void Render();
};
