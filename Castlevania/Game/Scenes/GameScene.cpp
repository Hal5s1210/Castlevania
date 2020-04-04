#include "GameScene.h"


void GameScene::Load()
{
	x = 0;
	y = 48;
	LoadFromFile();

	//simon = dynamic_cast<Simon*>(player);
	Sound::GetInstance()->Play(SOUND_COUNTYARD_ID);
	OutputDebugString(L"[INFO] GameScene loaded OK\n");
}

void GameScene::Unload()
{
	delete simon;

	Textures::GetInstance()->Clear();

	OutputDebugString(L"[INFO] GameScene ended OK\n");
}

void GameScene::Update(DWORD dt)
{
	simon->Update(dt, &objects);
	float simon_x, simon_y;
	simon->GetPosition(simon_x, simon_y);
	Viewport::GetInstance()->SetPosition(simon_x - 112, 0);
	AdjustView();
}

void GameScene::Render()
{
	tilemap->Render(x, y);
	simon->Render(x, y);
}

void GameScene::AdjustView()
{
	float cam_x, cam_y;
	Viewport::GetInstance()->GetPosition(cam_x, cam_y);

	if (cam_x < 0) cam_x = 0;
	if (cam_x > 512) cam_x = 512;

	Viewport::GetInstance()->SetPosition(cam_x, cam_y);
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
			{
				simon->ReadySubWeapon();
				simon->Attack(false);
			}
			else if (Input::GetInstance()->IsKeyDown(PAD_DOWN))
			{
				simon->ReadyWeapon();
				simon->Attack(true);
			}
			else
			{
				simon->ReadyWeapon();
				simon->Attack(false);
			}
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
}