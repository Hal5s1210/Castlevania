#include "Castlevania.h"
#include "Debug.h"
#include "Texture.h"
#include "Sprite.h"


Castlevania::Castlevania()
{
	d3ddv = 0;
	spriteHandler = 0;
}

Castlevania::~Castlevania()
{
}

void Castlevania::LoadResources()
{
	d3ddv = Graphics::GetInstance()->GetDirect3DDevice();
	spriteHandler = Graphics::GetInstance()->GetSpriteHandler();

	scenes = Scenes::GetInstance();
	scenes->LoadResource();

}

void Castlevania::Update(DWORD dt)
{
	Input::GetInstance()->GetKeyHandler(scenes->GetKeyHandler());
	Input::GetInstance()->ProcessKeyboard();

	scenes->Update(dt);
}

void Castlevania::Render()
{
	Graphics::GetInstance()->FillColor();

	if (SUCCEEDED(d3ddv->BeginScene()))
	{
		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		scenes->Render();

		spriteHandler->End();

		d3ddv->EndScene();
	}

	d3ddv->Present(NULL, NULL, NULL, NULL);
}