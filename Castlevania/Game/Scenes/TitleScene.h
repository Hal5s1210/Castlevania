#pragma once

#include "Scene.h" 

class TitleScene : public Scene
{
private:
	bool enter;
	DWORD time = -1;

	void Enter();

public:
	void LoadScene();
	void UpdateScene(DWORD dt);
	void EndScene();
	void RenderScene();

	void KeyState(BYTE* state);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);

};







