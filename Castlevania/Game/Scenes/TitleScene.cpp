#include "TitleScene.h"

void TitleScene::Load()
{
	Scene::Load();
	board = Board::GetInstance();
	board->LoadTexture();
	Viewport::GetInstance()->SetPosition(0, 0);
	time = -1;
}

void TitleScene::Unload()
{
	Scene::Unload();
}

void TitleScene::Update(DWORD dt)
{
	grid->GetObjectlist(&objects);

	for (LPGAMEOBJECT o : objects)
	{
		o->Update(dt);
		if (enter && time == -1)
		{
			if (dynamic_cast<TitleBat*>(o))
			{
				dynamic_cast<TitleBat*>(o)->PauseAnimation();
			}
			else if (dynamic_cast<TitleEnter*>(o))
			{
				dynamic_cast<TitleEnter*>(o)->SetAnimation(1);
			}
		}
	}

	if (enter)
	{
		if (time == -1) time = GetTickCount();
		if (GetTickCount() - time >= 2000)
		{
			Scenes::GetInstance()->NextScene(SCENE1_ID);
		}
	}
}

void TitleScene::Render()
{
	for (LPGAMEOBJECT o : objects)
	{
		o->Render();
	}
}




void TitleSceneKeyHandler::KeyState(BYTE* state)
{
}
void TitleSceneKeyHandler::OnKeyDown(int KeyCode)
{
	if (KeyCode == BUTTON_START)
	{
		dynamic_cast<TitleScene*>(scene)->Enter();
	}
}
void TitleSceneKeyHandler::OnKeyUp(int KeyCode)
{
}