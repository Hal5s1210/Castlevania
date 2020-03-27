#include "Castlevania.h"
#include "..\Framework\Debug.h"
#include "Scenes\TitleScene.h"
#include "Scenes\IntroScene.h"
#include "Scenes\GameScene.h"


Castlevania::Castlevania()
{
	d3ddv = 0;
	spriteHandler = 0;
	scenes = Scenes::GetInstance();
}

Castlevania::~Castlevania()
{
}

void Castlevania::LoadResources()
{
	d3ddv = Graphics::GetInstance()->GetDirect3DDevice();
	spriteHandler = Graphics::GetInstance()->GetSpriteHandler();

	scenes->Add(new TitleScene);
	//scenes->Add(new IntroScene);

}

void Castlevania::Update(DWORD dt)
{
	Input::GetInstance()->GetKeyHandler(scenes->GetKeyHandler());
	Input::GetInstance()->ProcessKeyboard();

	Scenes::GetInstance()->GetScene()->Update(dt);

}

void Castlevania::Render()
{
	Graphics::GetInstance()->FillColor();

	if (SUCCEEDED(d3ddv->BeginScene()))
	{
		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		Scenes::GetInstance()->GetScene()->Render();

		spriteHandler->End();

		d3ddv->EndScene();
	}

	d3ddv->Present(NULL, NULL, NULL, NULL);
}