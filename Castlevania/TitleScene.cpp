#include "TitleScene.h"
#include "Keyboard.h"

void TitleScene::LoadScene()
{
	id = TITLE_SCENE_ID;

	bg = new TitleBG;
	bg->SetAnimation(TITLE_BG_ANIMATION_ID);
	bg->SetPosition(0, 0);

	bat = new TitleBat;
	bat->SetAnimation(TITLE_BAT_ANIMATION_1_ID);
	bat->SetPosition(184, 104);

	text = new StartText;
	text->SetAnimation(START_TEXT_ANIMATION_1_ID);
	text->SetPosition(72, 136);

	sceneStart = true;
	OutputDebugString(L"[INFO] TitleScene loaded OK\n");
}

void TitleScene::EndScene()
{
	delete bg;
	delete bat;
	delete text;
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
	bg->Render();

	if (enter)
		bat->PauseAnimation();

	bat->Render();
	if (bat->GetFrame() == 0)
	{
		bat->SetAnimation(TITLE_BAT_ANIMATION_2_ID);
	}

	text->Render();
}

void TitleScene::ButtonDown(int keyCode)
{
	if (keyCode == BUTTON_START)
	{
		if (!enter)
		{
			enter = true;
			text->SetAnimation(START_TEXT_ANIMATION_2_ID);
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
	Animations* animations = Animations::GetInstance();
	LPDIRECT3DTEXTURE9 texture = Textures::GetInstance()->Get(TITLE_SCENE_TEX_ID);

	sprites->Add(TITLE_BG_SPRITE_ID, 1, 1, 257, 241, texture);

	LPANIMATION ani = new Animation;
	ani->AddFrame(TITLE_BG_SPRITE_ID);
	animations->Add(TITLE_BG_ANIMATION_ID, ani);
}

TitleBG::~TitleBG()
{
	Sprites* sprites = Sprites::GetInstance();
	Animations* animations = Animations::GetInstance();

	animations->Remove(TITLE_BG_ANIMATION_ID);
	sprites->Remove(TITLE_BG_SPRITE_ID);
}

void TitleBG::Render()
{
	animation->Draw(x, y);
}

#pragma endregion

#pragma region TitleBat

TitleBat::TitleBat()
{
	Sprites* sprites = Sprites::GetInstance();
	Animations* animations = Animations::GetInstance();
	LPDIRECT3DTEXTURE9 texture = Textures::GetInstance()->Get(TITLE_SCENE_TEX_ID);

	int i = 0;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			int l = x * 73 + 1;
			int t = y * 57 + 256;
			int r = l + 72;
			int b = t + 56;

			sprites->Add(TITLE_BAT_SPRITE_ID + i, l, t, r, b, texture);
			i++;
		}
	}

	int bat_id = TITLE_BAT_SPRITE_ID;

	LPANIMATION ani1 = new Animation;
	for (i = 0; i < 37; i++)
		ani1->AddFrame(TITLE_BAT_SPRITE_ID + i, 50);
	animations->Add(TITLE_BAT_ANIMATION_1_ID, ani1);

	LPANIMATION ani2 = new Animation;
	ani2->AddFrame(TITLE_BAT_SPRITE_ID + 37, 50);
	ani2->AddFrame(TITLE_BAT_SPRITE_ID + 38, 50);
	ani2->AddFrame(TITLE_BAT_SPRITE_ID + 39, 50);
	ani2->AddFrame(TITLE_BAT_SPRITE_ID + 38, 50);
	animations->Add(TITLE_BAT_ANIMATION_2_ID, ani2);
}

void TitleBat::Render()
{
	animation->Draw(x, y);
}

TitleBat::~TitleBat()
{
	Sprites* sprites = Sprites::GetInstance();
	Animations* animations = Animations::GetInstance();

	animations->Remove(TITLE_BAT_ANIMATION_1_ID);
	animations->Remove(TITLE_BAT_ANIMATION_2_ID);
	for (int i = 0; i < 40; i++)
		sprites->Remove(TITLE_BAT_SPRITE_ID + i);
}

#pragma endregion

#pragma region StartText

StartText::StartText()
{
	Sprites* sprites = Sprites::GetInstance();
	Animations* animations = Animations::GetInstance();
	LPDIRECT3DTEXTURE9 texture = Textures::GetInstance()->Get(TITLE_SCENE_TEX_ID);

	sprites->Add(START_TEXT_SPRITE_1_ID, 558, 1, 670, 9, texture);
	sprites->Add(START_TEXT_SPRITE_2_ID, 558, 10, 670, 18, texture);

	LPANIMATION ani1 = new Animation;
	ani1->AddFrame(START_TEXT_SPRITE_1_ID);
	animations->Add(START_TEXT_ANIMATION_1_ID, ani1);

	LPANIMATION ani2 = new Animation;
	ani2->AddFrame(START_TEXT_SPRITE_1_ID);
	ani2->AddFrame(START_TEXT_SPRITE_2_ID);
	animations->Add(START_TEXT_ANIMATION_2_ID, ani2);
}

void StartText::Render()
{
	animation->Draw(x, y);
}

StartText::~StartText()
{
	Sprites* sprites = Sprites::GetInstance();
	Animations* animations = Animations::GetInstance();

	animations->Remove(START_TEXT_ANIMATION_1_ID);
	animations->Remove(START_TEXT_ANIMATION_2_ID);
	sprites->Remove(START_TEXT_SPRITE_1_ID);
	sprites->Remove(START_TEXT_SPRITE_2_ID);
}

#pragma endregion