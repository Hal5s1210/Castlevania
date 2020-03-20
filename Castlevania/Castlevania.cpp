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

	scenes = Scenes::GetInstance();
	scenes->LoadResource();

}

void Castlevania::Update(DWORD dt)
{
	scenes->Update(dt);
}

void Castlevania::Render()
{
	Game::GetInstance()->FillColor();

	if (SUCCEEDED(d3ddv->BeginScene()))
	{
		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		scenes->Render();

		spriteHandler->End();

		d3ddv->EndScene();
	}

	d3ddv->Present(NULL, NULL, NULL, NULL);
}

LPKEYEVENTHANDLER Castlevania::GetKeyHandler()
{
	if (!keyHandler) keyHandler = new Keyboard;
	return keyHandler;
}