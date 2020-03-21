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
	void ButtonDown(int keyCode);
	void ButtonUp(int keyCode);

};

