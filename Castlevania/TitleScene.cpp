#include "TitleScene.h"
#include "Keyboard.h"

void TitleScene::LoadScene()
{
	id = TITLE_SCENE_ID;

	Textures::GetInstance()->Add(TITLE_BG_TEX_ID, TITLE_BG_TEX_DIR, D3DCOLOR_XRGB(0, 128, 0));
	Textures::GetInstance()->Add(TITLE_BAT_TEX_ID, TITLE_BAT_TEX_DIR, D3DCOLOR_XRGB(0, 128, 0));
	Textures::GetInstance()->Add(TITLE_TEXT_TEX_ID, TITLE_TEXT_TEX_DIR, D3DCOLOR_XRGB(0, 128, 0));

	bg = new TitleBG;
	bg->SetSprite(TITLE_BG_SPRITE_ID);
	bg->SetPosition(0, 0);
	mapObjs.push_back(bg);

	bat = new TitleBat;
	bat->SetSprite(TITLE_BAT_SPRITE_1_ID);
	bat->SetPosition(184, 104);
	mapObjs.push_back(bat);

	text = new StartText;
	text->SetSprite(TITLE_TEXT_SPRITE_1_ID);
	text->SetPosition(72, 136);
	mapObjs.push_back(text);

	sceneStart = true;
	OutputDebugString(L"[INFO] TitleScene loaded OK\n");
}

void TitleScene::EndScene()
{
	delete bg;
	delete bat;
	delete text;

	Textures::GetInstance()->Remove(TITLE_BG_TEX_ID);
	Textures::GetInstance()->Remove(TITLE_BAT_TEX_ID);
	Textures::GetInstance()->Remove(TITLE_TEXT_TEX_ID);

	OutputDebugString(L"[INFO] TitleScene ended OK\n");
	Scenes::GetInstance()->NextScene();
}

void TitleScene::Update(DWORD dt)
{
	if (enter)
	{
		if (time == -1)
			time = GetTickCount();

		DWORD now = GetTickCount();

		if (now - time > 2000)
			sceneEnd = true;
	}
}

void TitleScene::Render()
{
	if (enter)
		bat->PauseAnimation();

	if (bat->GetFrame() == 39)
	{
		bat->SetSprite(TITLE_BAT_SPRITE_2_ID);
	}

	for (LPGAMEOBJECT o : mapObjs)
		o->Render();
}

void TitleScene::ButtonDown(int keyCode)
{
	if (keyCode == BUTTON_START)
	{
		if (!enter)
		{
			enter = true;
			text->SetSprite(TITLE_TEXT_SPRITE_2_ID);
		}
	}
}

void TitleScene::ButtonUp(int keyCode)
{

}


#pragma region TitleBG

TitleBG::TitleBG()
{
	Sprites* sprites = Sprites::GetInstance();
	LPDIRECT3DTEXTURE9 texture = Textures::GetInstance()->Get(TITLE_BG_TEX_ID);

	LPSPRITE s = new Sprite(texture);
	s->AddFrame(0, 0, 256, 240);
	sprites->Add(TITLE_BG_SPRITE_ID, s);
}

TitleBG::~TitleBG()
{
	Sprites* sprites = Sprites::GetInstance();
	sprites->Remove(TITLE_BG_SPRITE_ID);
}

void TitleBG::Render()
{
	sprite->Draw(x, y);
}

#pragma endregion

#pragma region TitleBat

TitleBat::TitleBat()
{
	Sprites* sprites = Sprites::GetInstance();
	LPDIRECT3DTEXTURE9 texture = Textures::GetInstance()->Get(TITLE_BAT_TEX_ID);

	LPSPRITE s1 = new Sprite(texture);
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 10; x++)
		{ 
			s1->AddFrame(x * 72, y * 56, 72, 56, 50);
		}
	}
	sprites->Add(TITLE_BAT_SPRITE_1_ID, s1);

	LPSPRITE s2 = new Sprite(texture);
	s2->AddFrame(576, 168, 72, 56, 50);
	s2->AddFrame(504, 168, 72, 56, 50);
	s2->AddFrame(576, 168, 72, 56, 50);
	s2->AddFrame(648, 168, 72, 56, 50);
	sprites->Add(TITLE_BAT_SPRITE_2_ID, s2);
}

void TitleBat::Render()
{
	sprite->Draw(x, y);
}

TitleBat::~TitleBat()
{
	Sprites* sprites = Sprites::GetInstance();
	sprites->Remove(TITLE_BAT_SPRITE_1_ID);
	sprites->Remove(TITLE_BAT_SPRITE_2_ID);
}

#pragma endregion

#pragma region StartText

StartText::StartText()
{
	Sprites* sprites = Sprites::GetInstance();
	LPDIRECT3DTEXTURE9 texture = Textures::GetInstance()->Get(TITLE_TEXT_TEX_ID);

	LPSPRITE s1 = new Sprite(texture);
	s1->AddFrame(0, 0, 112, 8);
	sprites->Add(TITLE_TEXT_SPRITE_1_ID, s1);

	LPSPRITE s2 = new Sprite(texture);
	s2->AddFrame(0, 0, 112, 8);
	s2->AddFrame(0, 8, 112, 8);
	sprites->Add(TITLE_TEXT_SPRITE_2_ID, s2);
}

void StartText::Render()
{
	sprite->Draw(x, y);
}

StartText::~StartText()
{
	Sprites* sprites = Sprites::GetInstance();
	sprites->Remove(TITLE_TEXT_SPRITE_1_ID);
	sprites->Remove(TITLE_TEXT_SPRITE_2_ID);
}

#pragma endregion