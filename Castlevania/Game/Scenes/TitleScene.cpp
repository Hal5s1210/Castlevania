#include "TitleScene.h"

void TitleScene::Load()
{
	Scene::Load();
	board = Board::GetInstance();
	board->LoadTexture();
	Viewport::GetInstance()->SetPosition(0, 0);
	enter = false;
	time = 0;
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
		if (enter && time == 0)
		{
			SimpleObject* s = dynamic_cast<SimpleObject*>(o);
			if (s->GetName() == "Bat")
			{
				s->PauseAnimation();
			}
			else if (s->GetName() == "Text")
			{
				s->SetAnimation(1);
			}
		}
	}

	if (enter)
	{
		if (time == 0) time = GetTickCount();
		if (GetTickCount() - time >= 2000)
		{
			Scenes::GetInstance()->NextScene(INTRO_ID);
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