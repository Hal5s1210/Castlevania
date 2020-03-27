#pragma once

#include "..\..\Framework\Scene.h" 

class TitleScene : public Scene
{
private:
	bool enter;
	DWORD time = -1;

public:
	void LoadScene();
	void UpdateScene(DWORD dt);
	void EndScene();
	void RenderScene();

	void Enter();

};

class TitleKeyHandler : public KeyEventHandler
{
public:
	TitleKeyHandler(Scene* s) :KeyEventHandler(s) {}
	void KeyState(BYTE* state);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
};







