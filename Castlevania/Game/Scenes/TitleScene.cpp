#include "TitleScene.h"

void TitleScene::LoadScene()
{
	x = y = 0;
	LoadFromFile(L"Resources\\XML\\TitleScene.xml");

	OutputDebugString(L"[INFO] TitleScene loaded OK\n");
	sceneStart = true;
}

void TitleScene::EndScene()
{
	for (LPGAMEOBJECT o : mapObjs)
		delete o;

	Textures::GetInstance()->Clear();

	OutputDebugString(L"[INFO] TitleScene ended OK\n");
}

void TitleScene::UpdateScene(DWORD dt)
{
	if (enter)
	{
		if (time == -1)
			time = GetTickCount();

		DWORD now = GetTickCount();

		if (now - time > 2000)
		{
			sceneEnd = true;
			Scenes::GetInstance()->NextScene();
		}
	}

	for (LPGAMEOBJECT o : mapObjs)
		o->Update(dt);
}

void TitleScene::RenderScene()
{
	if (enter)
	{
		for (LPGAMEOBJECT o : mapObjs)
		{
			if (dynamic_cast<TitleBat*>(o))
			{
				o->PauseAnimation();
			}
		}
	}

	for (LPGAMEOBJECT o : mapObjs)
		o->Render(x, y);
}

void TitleScene::Enter()
{
	if (!enter)
	{
		enter = true;
		for (LPGAMEOBJECT o : mapObjs)
		{
			if (dynamic_cast<TitleText*>(o))
			{
				o->SetAnimation("ani2");
			}
		}
	}
}

void TitleScene::KeyState(BYTE* state) 
{
}

void TitleScene::OnKeyDown(int KeyCode)
{
	if (KeyCode == BUTTON_START)
	{
		Enter();
	}
}

void TitleScene::OnKeyUp(int KeyCode)
{
}