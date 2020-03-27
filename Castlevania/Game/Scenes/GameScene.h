#pragma once

#include "..\..\Framework\Scene.h"
#include "..\Objects\Simon.h"

class GameScene : public Scene
{
private:
	Simon* simon;

public:
	void LoadScene();
	void EndScene();
	void UpdateScene(DWORD dt);
	void RenderScene();

	Simon* GetSimon() { return simon; }

};

class GameKeyHandler : public KeyEventHandler
{
public:
	GameKeyHandler(Scene* s) :KeyEventHandler(s) {}
	void KeyState(BYTE* state);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
};

