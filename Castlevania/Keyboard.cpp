#include "Keyboard.h"
#include "Debug.h"
#include "Scene.h"
#include "TitleScene.h"


void Keyboard::KeyState(BYTE* state)
{
}

void Keyboard::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	LPSCENE scene = Scenes::GetInstance()->CurrentScene();
	if (!scene) return;

	scene->ButtonDown(KeyCode);
}

void Keyboard::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	LPSCENE scene = Scenes::GetInstance()->CurrentScene();
	if (!scene) return;

	scene->ButtonUp(KeyCode);
}
