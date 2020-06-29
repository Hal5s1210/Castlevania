#pragma once

#include "Scene.h"

class PlaySceneKeyHandler : public KeyEventHandler
{
	LPSCENE scene;
public:
	PlaySceneKeyHandler(LPSCENE s) :scene(s) {}

	void KeyState(BYTE* state);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
};


class PlayScene : public Scene
{
private:
	void AdjustView();

public:
	PlayScene(float x, float y, std::wstring filepath) : Scene(x, y, filepath)
	{
		keyhandler = new PlaySceneKeyHandler(this);
	}

	void Reset();
	void Load();
	void Unload();
	void Update(DWORD dt);
	void Render();
};

