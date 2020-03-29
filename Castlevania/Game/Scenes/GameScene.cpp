#include "GameScene.h"


void GameScene::LoadScene()
{
	x = 0;
	y = 48;
	LoadFromFile(L"Resources\\XML\\GameScene.xml");

	simon = dynamic_cast<Simon*>(player);

	OutputDebugString(L"[INFO] GameScene loaded OK\n");
	sceneStart = true;
}

void GameScene::EndScene()
{
	delete simon;

	Textures::GetInstance()->Clear();

	OutputDebugString(L"[INFO] GameScene ended OK\n");
}

void GameScene::UpdateScene(DWORD dt)
{
	simon->Update(dt, &mapObjs);
}

void GameScene::RenderScene()
{
	map->Render(x, y);
	for (LPGAMEOBJECT o : mapObjs)
	{
		o->Render(x, y);
	}
	simon->Render(x, y);
}





void GameScene::KeyState(BYTE* state)
{
	Input* input = Input::GetInstance();
	if (simon)
	{
		if (input->IsKeyDown(PAD_LEFT))
			simon->GoLeft();
		else if (input->IsKeyDown(PAD_RIGHT))
			simon->GoRight();
		else if (input->IsKeyDown(PAD_DOWN))
			simon->Crounch();
		else simon->GoIdle();
	}
}

void  GameScene::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	if (simon)
	{
		switch (KeyCode)
		{
		case BUTTON_A:
			if (Input::GetInstance()->IsKeyDown(PAD_UP))
				simon->SubAttack();
			else if (Input::GetInstance()->IsKeyDown(PAD_DOWN))
				simon->Attack(true);
			else simon->Attack(false);
			break;

		case BUTTON_B:
			simon->Jump();
			break;

		}
	}
}

void  GameScene::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	/*if (simon)
	{
		switch (KeyCode)
		{
		case PAD_LEFT:
			simon->GoLeft(false);
			break;

		case PAD_RIGHT:
			simon->GoRight(false);
			break;

		case PAD_DOWN:
			simon->Crounch(false);
			break;

		}
	}*/
}