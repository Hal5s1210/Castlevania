#include "GameScene.h"
#include "Keyboard.h"

void GameScene::LoadScene()
{
	Textures::GetInstance()->Add(SIMON_TEX_ID, SIMON_TEX_DIR, D3DCOLOR_XRGB(116, 116, 116));

	simon = new Simon;
	simon->SetPosition(132, 88);

	OutputDebugString(L"[INFO] GameScene loaded OK\n");
	sceneStart = true;
}

void GameScene::EndScene()
{
	delete simon;

	Textures* textures = Textures::GetInstance();
	textures->Remove(SIMON_TEX_ID);

	OutputDebugString(L"[INFO] GameScene ended OK\n");
}

void GameScene::Update(DWORD dt)
{
	simon->Update(dt, NULL);
}

void GameScene::Render()
{
	simon->Render();
}

void GameScene::ButtonDown(int keyCode)
{
	if (simon)
	{
		switch (keyCode)
		{
		case PAD_LEFT:
			simon->SetState(SIMON_STATE_WALK_LEFT);
			break;

		case PAD_RIGHT:
			simon->SetState(SIMON_STATE_WALK_RIGHT);
			break;
		}

	}
}

void GameScene::ButtonUp(int keyCode)
{
	if (simon)
	{
		switch (keyCode)
		{
		case PAD_LEFT:
		case PAD_RIGHT:
			if (simon->GetState() != SIMON_STATE_IDLE)
				simon->SetState(SIMON_STATE_IDLE);
			break;

		}

	}
}