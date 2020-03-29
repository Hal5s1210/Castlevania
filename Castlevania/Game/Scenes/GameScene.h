#pragma once

#include "Scene.h"
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

	void KeyState(BYTE* state);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);

	Simon* GetSimon() { return simon; }
};

