#include "TitleScene.h"

void TitleScene::LoadScene()
{
	keyHandler = new TitleKeyHandler;
	id = TITLE_SCENE_ID;
	Textures::GetInstance()->Add(TITLE_BG_TEX_ID, TITLE_BG_TEX_DIR, D3DCOLOR_XRGB(0, 128, 0));
	Textures::GetInstance()->Add(TITLE_BAT_TEX_ID, TITLE_BAT_TEX_DIR, D3DCOLOR_XRGB(0, 128, 0));
	Textures::GetInstance()->Add(TITLE_TEXT_TEX_ID, TITLE_TEXT_TEX_DIR, D3DCOLOR_XRGB(0, 128, 0));

	bg = new TitleBG;
	bg->SetPosition(0, 0);
	mapObjs.push_back(bg);

	bat = new TitleBat;
	bat->SetPosition(184, 104);
	mapObjs.push_back(bat);

	text = new StartText;
	text->SetPosition(72, 136);
	mapObjs.push_back(text);

	OutputDebugString(L"[INFO] TitleScene loaded OK\n");
	sceneStart = true;
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

	for (LPGAMEOBJECT o : mapObjs)
		o->Update(dt);
}

void TitleScene::Render()
{
	if (enter)
		bat->PauseAnimation();

	for (LPGAMEOBJECT o : mapObjs)
		o->Render();
}

void TitleScene::Enter()
{
	if (!enter)
	{
		enter = true;
		text->SetAnimation(TITLE_TEXT_ANIMATION_2);
	}
}



void TitleKeyHandler::KeyState(BYTE* state) 
{
}

void TitleKeyHandler::OnKeyDown(int KeyCode)
{
	if (KeyCode == BUTTON_START)
	{
		Enter();
	}
}

void TitleKeyHandler::OnKeyUp(int KeyCode)
{
}



#pragma region TitleBG

TitleBG::TitleBG()
{
	LPTEXTURE texture = Textures::GetInstance()->Get(TITLE_BG_TEX_ID);

	LPANIMATION s = new Animation(texture);
	s->AddFrame(0, 0, 256, 240);
	AddAnimation(s);

	SetAnimation(TITLE_BG_ANIMATION);
}

TitleBG::~TitleBG()
{
	animations.clear();
}

void TitleBG::Render()
{
	animations[currentAnimation]->Draw(x, y);
}

#pragma endregion




#pragma region TitleBat

TitleBat::TitleBat()
{
	LPTEXTURE texture = Textures::GetInstance()->Get(TITLE_BAT_TEX_ID);

	LPANIMATION s1 = new Animation(texture);
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 10; x++)
		{ 
			s1->AddFrame(x * 72, y * 56, 72, 56, 50);
		}
	}
	AddAnimation(s1);

	LPANIMATION s2 = new Animation(texture);
	s2->AddFrame(576, 168, 72, 56, 50);
	s2->AddFrame(504, 168, 72, 56, 50);
	s2->AddFrame(576, 168, 72, 56, 50);
	s2->AddFrame(648, 168, 72, 56, 50);
	AddAnimation(s2);

	SetAnimation(TITLE_BAT_ANIMATION_1);
}

void TitleBat::Update(DWORD dt)
{
	if (animations[currentAnimation]->CurrentFrameIndex() == 39)
	{
		SetAnimation(TITLE_BAT_ANIMATION_2);
	}
}

void TitleBat::Render()
{
	animations[currentAnimation]->Draw(x, y);

}

TitleBat::~TitleBat()
{
	animations.clear();
}

#pragma endregion




#pragma region StartText

StartText::StartText()
{
	LPTEXTURE texture = Textures::GetInstance()->Get(TITLE_TEXT_TEX_ID);

	LPANIMATION s1 = new Animation(texture);
	s1->AddFrame(0, 0, 112, 8);
	AddAnimation(s1);

	LPANIMATION s2 = new Animation(texture);
	s2->AddFrame(0, 0, 112, 8);
	s2->AddFrame(0, 8, 112, 8);
	AddAnimation(s2);

	SetAnimation(TITLE_TEXT_ANIMATION_1);
}

void StartText::Render()
{
	animations[currentAnimation]->Draw(x, y);
}

StartText::~StartText()
{
	animations.clear();
}

#pragma endregion