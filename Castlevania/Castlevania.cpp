#include "Castlevania.h"
#include "Debug.h"


#pragma region Castlavania Class

Castlevania::Castlevania()
{
	keyHandler = 0;
}

Castlevania::~Castlevania()
{
}

void Castlevania::LoadResources()
{
	d3ddv = Game::GetInstance()->GetDirect3DDevice();
	spriteHandler = Game::GetInstance()->GetSpriteHandler();
}

void Castlevania::Update(DWORD dt)
{
}

void Castlevania::Render()
{
	if (d3ddv->BeginScene())
	{
		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);



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

#pragma endregion



#pragma region GameKeyHandler Class

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