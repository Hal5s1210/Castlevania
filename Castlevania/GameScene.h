#pragma once

#include "Scene.h"
#include "Simon.h"

class GameScene : public Scene
{
private:
	Simon* simon;

public:
	void LoadScene();
	void EndScene();
	void Update(DWORD dt);
	void Render();

};

class GameKeyHandler : public KeyEventHandler
{
public:
	void KeyState(BYTE* state);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
};

