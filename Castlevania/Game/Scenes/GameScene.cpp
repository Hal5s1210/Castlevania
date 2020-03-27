#include "GameScene.h"

void GameScene::LoadScene()
{
	keyHandler = new GameKeyHandler(this);
	Textures::GetInstance()->Add(SIMON_TEX_ID, SIMON_TEX_DIR, D3DCOLOR_XRGB(116, 116, 116));
	Textures::GetInstance()->Add(-100, L"Resources\\Textures\\red.bmp", D3DCOLOR_XRGB(116, 116, 116));

	simon = new Simon;
	simon->SetPosition(132, 108);

	for (int i = 0; i < 10; i++)
	{
		Platform* p = new Platform;
		p->SetPosition(16 * i + 48, 160);
		mapObjs.push_back(p);
	}

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

void GameScene::UpdateScene(DWORD dt)
{
	simon->Update(dt, &mapObjs);
}

void GameScene::RenderScene()
{
	for (LPGAMEOBJECT o : mapObjs)
	{
		o->Render();
	}
	simon->Render();
}





void GameKeyHandler::KeyState(BYTE* state)
{
}

void GameKeyHandler::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	Simon* simon = dynamic_cast<GameScene*>(scene)->GetSimon();

	if (simon)
	{
		switch (KeyCode)
		{
		case PAD_LEFT:
			simon->GoLeft(true);
			break;

		case PAD_RIGHT:
			simon->GoRight(true);
			break;

		case PAD_DOWN:
			simon->Crounch(true);
			break;

		case BUTTON_A:
			simon->Attack();
			break;

		case BUTTON_B:
			simon->Jump();
			break;

		}
	}
}

void GameKeyHandler::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	Simon* simon = dynamic_cast<GameScene*>(scene)->GetSimon();

	if (simon)
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
	}
}