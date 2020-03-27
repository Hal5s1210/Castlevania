#include "TitleScene.h"
#include "..\Objects\ObjectGenerator.h"

void TitleScene::LoadScene()
{
	keyHandler = new TitleKeyHandler(this);
	id = TITLE_SCENE_ID;

	generator = ObjectGenerator::GetInstance();
	LoadFromFile(L"Resources\\XML\\TitleScene.xml");

	OutputDebugString(L"[INFO] TitleScene loaded OK\n");
	sceneStart = true;
}

void TitleScene::EndScene()
{
	for (LPGAMEOBJECT o : mapObjs)
		delete o;

	Textures::GetInstance()->Remove(1);
	Textures::GetInstance()->Remove(2);
	Textures::GetInstance()->Remove(3);

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
			sceneEnd = true;
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
		o->Render();
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
				o->SetAnimation(TITLE_TEXT_ANIMATION_2);
			}
		}
	}
}




void TitleKeyHandler::KeyState(BYTE* state) 
{
}

void TitleKeyHandler::OnKeyDown(int KeyCode)
{
	if (KeyCode == BUTTON_START)
	{
		dynamic_cast<TitleScene*>(scene)->Enter();
	}
}

void TitleKeyHandler::OnKeyUp(int KeyCode)
{
}