#pragma once

#include "Scene.h"

class TitleSceneKeyHandler : public KeyEventHandler
{
	LPSCENE scene;
public:
	TitleSceneKeyHandler(LPSCENE s) :scene(s) {}

	void KeyState(BYTE* state);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
};


class TitleScene : public Scene
{
private:
	DWORD time;
	bool enter;
	
public:
	TitleScene(float x, float y, std::wstring filepath) : Scene(x, y, filepath)
	{
		keyhandler = new TitleSceneKeyHandler(this);
	}

	void Enter() { enter = true; }

	void Load();
	void Unload();
	void Update(DWORD dt);
	void Render();
};

