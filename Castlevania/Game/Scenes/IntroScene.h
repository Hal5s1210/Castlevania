#pragma once

#include "Scene.h"

class IntroScene : public Scene
{
private:
	DWORD time;
	bool soundplay;

public:
	void LoadScene();
	void EndScene();
	void UpdateScene(DWORD dt);
	void RenderScene();

	void KeyState(BYTE* state) {}
	void OnKeyDown(int KeyCode) {}
	void OnKeyUp(int KeyCode) {}

};

