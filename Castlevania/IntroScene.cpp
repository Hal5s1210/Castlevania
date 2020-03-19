#include "IntroScene.h"

void IntroScene::LoadScene()
{
	bg = new IntroBG;
	bg->SetAnimation(INTRO_BG_ANIMATION_ID);
	bg->SetPosition(0, 48);

	OutputDebugString(L"[INFO] IntroScene loaded OK\n");
	sceneStart = true;
}

void IntroScene::EndScene()
{
	delete bg;

	OutputDebugString(L"[INFO] IntroScene ended OK\n");
	Scenes::GetInstance()->NextScene();
}

void IntroScene::Update(DWORD dt)
{
}

void IntroScene::Render()
{
	bg->Render();
}

void IntroScene::ButtonDown(int keyCode)
{
}

void IntroScene::ButtonUp(int keyCode)
{
}


#pragma region IntroBG

IntroBG::IntroBG()
{
	Sprites* sprites = Sprites::GetInstance();
	Animations* animations = Animations::GetInstance();
	LPDIRECT3DTEXTURE9 texture = Textures::GetInstance()->Get(INTRO_SCENE_TEX_ID);

	sprites->Add(INTRO_BG_SPRITE_ID, 1, 1, 257, 193, texture);

	LPANIMATION ani = new Animation;
	ani->AddFrame(INTRO_BG_SPRITE_ID);
	animations->Add(INTRO_BG_ANIMATION_ID, ani);
}

IntroBG::~IntroBG()
{
	Sprites* sprites = Sprites::GetInstance();
	Animations* animations = Animations::GetInstance();

	animations->Remove(INTRO_BG_ANIMATION_ID);
	sprites->Remove(INTRO_BG_SPRITE_ID);
}

void IntroBG::Render()
{
	animation->Draw(x, y);
}

#pragma endregion
