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

	/*switch (KeyCode)
	{
	case BUTTON_START:
		if (scene->GetId() == TITLE_SCENE_ID)
		{
			scene->ButtonDown(BUTTON_START);
		}
		break;
	}*/
	scene->ButtonDown(KeyCode);
}

void Keyboard::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	LPSCENE scene = Scenes::GetInstance()->CurrentScene();
	if (!scene) return;

	/*switch (KeyCode)
	{
	case BUTTON_START:
		if (scene->GetId() == TITLE_SCENE_ID)
		{
			scene->ButtonUp(BUTTON_START);
		}
		break;
	}*/
	scene->ButtonUp(KeyCode);
}
