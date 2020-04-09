#include "GameScene.h"


void GameScene::Load()
{
	x = 0;
	y = 48;
	LoadFromFile();
	board = new Board;
	loaded = true;
	Sound::GetInstance()->Play(SOUND_COUNTYARD_ID);
	OutputDebugString(L"[INFO] GameScene loaded OK\n");
}

void GameScene::Unload()
{
	//delete simon;

	Textures::GetInstance()->Clear();
	loaded = false;
	OutputDebugString(L"[INFO] GameScene ended OK\n");
}

void GameScene::Update(DWORD dt)
{
	grid->GetObjectlist(&objects);

	player->Update(dt, &objects);


	float player_x, player_y;
	player->GetPosition(player_x, player_y);
	Viewport::GetInstance()->SetPosition(player_x - 112, 0);
	AdjustView();

	board->Update(dt);
}

void GameScene::Render()
{
	tilemap->Render(x, y);

	board->Render();

	for (LPGAMEOBJECT obj : objects)
	{
		obj->Render(x, y);
	}

	player->Render(x, y);
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
	if (player)
	{
		if (input->IsKeyDown(PAD_DOWN))
		{
			player->SetState(Simon::Crounch);
		}
		else if (input->IsKeyDown(PAD_LEFT))
		{
			player->SetState(Simon::WalkL);
		}
		else if (input->IsKeyDown(PAD_RIGHT))
		{
			player->SetState(Simon::WalkR);
		}
		else
		{
			player->SetState(Simon::Idle);
		}

	}

}

void  GameScene::OnKeyDown(int KeyCode)
{
	NSDebug::DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	if (player)
	{
		switch (KeyCode)
		{
		case BUTTON_A:
			if (Input::GetInstance()->IsKeyDown(PAD_UP))
			{
				player->SetState(Simon::SubWeapon);
			}
			else
			{
				player->SetState(Simon::Attack);
			}
			break;

		case BUTTON_B:
			player->SetState(Simon::Jump);
			break;

		}
	}

}

void  GameScene::OnKeyUp(int KeyCode)
{
	NSDebug::DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}