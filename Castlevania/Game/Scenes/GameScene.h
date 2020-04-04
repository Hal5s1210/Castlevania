#pragma once

#include "Scene.h"
#include "..\Objects\Simon.h"

class GameScene : public Scene
{
private:
	Simon* simon;
	void AdjustView();

public:
	GameScene(LPCWSTR filepath) :Scene(filepath) {}

	void Load();
	void Unload();
	void Update(DWORD dt);
	void Render();

	void KeyState(BYTE* state);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);

	Simon* GetSimon() { return simon; }
};

