#include "Castlevania.h"
#include "..\Framework\Debug.h"
#include "Scenes\PlayScene.h"
#include "Parser.h"


Castlevania::Castlevania()
{
	d3ddv = 0;
	spriteHandler = 0;
	board = Board::GetInstance();
	scenes = Scenes::GetInstance();
}

Castlevania::~Castlevania()
{
}

void Castlevania::LoadResources()
{
	d3ddv = Graphics::GetInstance()->GetDirect3DDevice();
	spriteHandler = Graphics::GetInstance()->GetSpriteHandler();

	Parser::Parse_Game(L"Resources\\XML\\Castlevania.xml");
}

void Castlevania::Update(DWORD dt)
{
	Scenes::GetInstance()->SwitchScene();

	LPSCENE scene = Scenes::GetInstance()->GetScene();
	Input::GetInstance()->GetKeyHandler(scene->GetKeyHandler());
	Input::GetInstance()->ProcessKeyboard();

	scene->Update(dt);

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