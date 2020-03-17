#include "Castlevania.h"
#include "Debug.h"
#include "Texture.h"
#include "Sprite.h"


Castlevania::Castlevania()
{
	d3ddv = 0;
	spriteHandler = 0;
	keyHandler = 0;
}

Castlevania::~Castlevania()
{
}

void Castlevania::LoadResources()
{
	d3ddv = Game::GetInstance()->GetDirect3DDevice();
	spriteHandler = Game::GetInstance()->GetSpriteHandler();

	Textures* textures = Textures::GetInstance();
	textures->Add(100, L"Resources\\Textures\\green.bmp", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(101, L"Resources\\Textures\\red.bmp", D3DCOLOR_XRGB(255, 255, 255));

	Sprites* sprites = Sprites::GetInstance();
	sprites->Add(1000, 0, 0, 20, 20, textures->Get(100));
	sprites->Add(1001, 0, 0, 20, 20, textures->Get(101));

	Animations* animations = Animations::GetInstance();

	LPANIMATION ani1 = new Animation;
	ani1->AddFrame(1000);
	animations->Add(1000, ani1);

	LPANIMATION ani2 = new Animation;
	ani2->AddFrame(1001);
	animations->Add(1001, ani2);


	player = new Block;
	player->AddAnimation(1000);
	player->SetPosition(100, 80);
	player->SetSpeed(0.05, 0.05);

	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 10; y++)
		{
			if (x == 0 || y == 0 || x == 9 || y == 9)
			{
				LPGAMEOBJECT o = new Block;
				o->AddAnimation(1001);
				o->SetPosition(x * 20 + 28, y * 20 + 20);
				objects.push_back(o);
			}
		}
	}

}

void Castlevania::Update(DWORD dt)
{
	player->Update(dt, &objects);
}

void Castlevania::Render()
{
	Game::GetInstance()->FillColor();

	if (SUCCEEDED(d3ddv->BeginScene()))
	{
		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		for (LPGAMEOBJECT o : objects)
		{
			o->Render();
		}
		player->Render();

		spriteHandler->End();

		d3ddv->EndScene();
	}

	d3ddv->Present(NULL, NULL, NULL, NULL);
}

LPKEYEVENTHANDLER Castlevania::GetKeyHandler()
{
	if (!keyHandler) keyHandler = new GameKeyHandler;
	return keyHandler;
}



#pragma region GameKeyHandler

void GameKeyHandler::KeyState(BYTE* state)
{
}

void GameKeyHandler::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_SPACE:
		break;
	}
}

void GameKeyHandler::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_SPACE:
		break;
	}
}

#pragma endregion