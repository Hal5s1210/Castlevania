#pragma once

#include "Scene.h"

class PlaySceneKeyHandler : public IKeyEventHandler
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
	PlayScene(int x, int y, LPCWSTR filepath) : Scene(x, y, filepath)
	{
		keyhandler = new PlaySceneKeyHandler(this);
	}

	void Load();
	void Unload();
	void Update(DWORD dt);
	void Render();
};

