#include "IntroScene.h"
#include "Simon.h"
#include "Sound.h"

void IntroScene::LoadScene()
{
	LPSOUND sound = Sound::GetInstance();
	sound->Load(INTRO_SONG_ID, INTRO_SONG_DIR);
	sound->Play(INTRO_SONG_ID);

	bg = new IntroBG;
	bg->SetAnimation(INTRO_BG_ANIMATION_ID);
	bg->SetPosition(0, 48);

	bat1 = new IntroBat;
	bat1->SetAnimation(INTRO_BAT_ANIMATION_ID);
	bat1->SetPosition(30, 108);
	bat1->SetSpeed(0.01, -0.007);

	bat2 = new IntroBat;
	bat2->SetAnimation(INTRO_BAT_ANIMATION_ID);
	bat2->SetPosition(160, 74);
	bat2->SetSpeed(-0.006, 0);

	cloud = new IntroCloud;
	cloud->SetAnimation(INTRO_CLOUD_ANIMATION_ID);
	cloud->SetPosition(240, 76);
	cloud->SetSpeed(-0.005, 0);

	simon = new IntroSimon;
	simon->SetAnimation(INTRO_SIMON_ANIMATION_1_ID);
	simon->SetPosition(240, 177);
	simon->SetSpeed(-0.02, 0);

	OutputDebugString(L"[INFO] IntroScene loaded OK\n");
	time = GetTickCount();
	sceneStart = true;
}

void IntroScene::EndScene()
{
	delete bg;
	delete bat1;
	delete bat2;
	delete cloud;
	delete simon;

	Sound::GetInstance()->Remove(INTRO_SONG_ID);

	OutputDebugString(L"[INFO] IntroScene ended OK\n");
	Scenes::GetInstance()->NextScene();
}

void IntroScene::Update(DWORD dt)
{
	float x, y;

	bat2->GetPosition(x, y);
	if (x <= 128)
		bat2->SetSpeed(-0.0015, -0.004);

	simon->GetPosition(x, y);
	if (x <= 120)
	{
		simon->SetAnimation(INTRO_SIMON_ANIMATION_2_ID);
		simon->SetSpeed(0, 0);
	}

	bat1->Update(dt);
	bat2->Update(dt);
	cloud->Update(dt);
	simon->Update(dt);

	if (GetTickCount() - time >= 7000)
		sceneEnd = true;
}

void IntroScene::Render()
{
	bg->Render();
	bat1->Render();
	bat2->Render();
	cloud->Render();
	simon->Render();
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

#pragma region IntroBat

IntroBat::IntroBat()
{
	Sprites* sprites = Sprites::GetInstance();
	Animations* animations = Animations::GetInstance();
	LPDIRECT3DTEXTURE9 texture = Textures::GetInstance()->Get(INTRO_SCENE_TEX_ID);

	sprites->Add(INTRO_BAT_SPRITE_1_ID, 1, 194, 9, 201, texture);
	sprites->Add(INTRO_BAT_SPRITE_2_ID, 10, 194, 18, 201, texture);

	LPANIMATION ani = new Animation;
	ani->AddFrame(INTRO_BAT_SPRITE_1_ID, 50);
	ani->AddFrame(INTRO_BAT_SPRITE_2_ID, 50);
	animations->Add(INTRO_BAT_ANIMATION_ID, ani);
}

IntroBat::~IntroBat()
{
	Sprites* sprites = Sprites::GetInstance();
	Animations* animations = Animations::GetInstance();

	animations->Remove(INTRO_BAT_ANIMATION_ID);
	sprites->Remove(INTRO_BAT_SPRITE_1_ID);
	sprites->Remove(INTRO_BAT_SPRITE_2_ID);
}

void IntroBat::Update(DWORD dt)
{
	GameObject::Update(dt);

	x += dx;
	y += dy;
}

void IntroBat::Render()
{
	animation->Draw(x, y);
}

#pragma endregion

#pragma region IntroCould

IntroCloud::IntroCloud()
{
	Sprites* sprites = Sprites::GetInstance();
	Animations* animations = Animations::GetInstance();
	LPDIRECT3DTEXTURE9 texture = Textures::GetInstance()->Get(INTRO_SCENE_TEX_ID);

	sprites->Add(INTRO_CLOUD_SPRITE_ID, 19, 194, 51, 210, texture);

	LPANIMATION ani = new Animation;
	ani->AddFrame(INTRO_CLOUD_SPRITE_ID);
	animations->Add(INTRO_CLOUD_ANIMATION_ID, ani);
}

IntroCloud::~IntroCloud()
{
	Sprites* sprites = Sprites::GetInstance();
	Animations* animations = Animations::GetInstance();

	animations->Remove(INTRO_CLOUD_ANIMATION_ID);
	sprites->Remove(INTRO_CLOUD_SPRITE_ID);
}

void IntroCloud::Update(DWORD dt)
{
	GameObject::Update(dt);

	x += dx;
	y += dy;
}

void IntroCloud::Render()
{
	animation->Draw(x, y);
}
#pragma endregion

#pragma region IntroSimon

IntroSimon::IntroSimon()
{
	Sprites* sprites = Sprites::GetInstance();
	Animations* animations = Animations::GetInstance();
	LPDIRECT3DTEXTURE9 texture = Textures::GetInstance()->Get(SIMON_TEX_ID);

	sprites->Add(INTRO_SIMON_SPRITE_1_ID, 29, 21, 45, 53, texture);
	sprites->Add(INTRO_SIMON_SPRITE_2_ID, 46, 21, 62, 53, texture);
	sprites->Add(INTRO_SIMON_SPRITE_3_ID, 63, 21, 79, 53, texture);
	sprites->Add(INTRO_SIMON_SPRITE_4_ID, 362, 21, 378, 53, texture);

	LPANIMATION ani1 = new Animation;
	ani1->AddFrame(INTRO_SIMON_SPRITE_1_ID, 180);
	ani1->AddFrame(INTRO_SIMON_SPRITE_2_ID, 180);
	ani1->AddFrame(INTRO_SIMON_SPRITE_3_ID, 180);
	ani1->AddFrame(INTRO_SIMON_SPRITE_2_ID, 180);
	animations->Add(INTRO_SIMON_ANIMATION_1_ID, ani1);

	LPANIMATION ani2 = new Animation;
	ani2->AddFrame(INTRO_SIMON_SPRITE_4_ID);
	animations->Add(INTRO_SIMON_ANIMATION_2_ID, ani2);
}
IntroSimon::~IntroSimon()
{
	Sprites* sprites = Sprites::GetInstance();
	Animations* animations = Animations::GetInstance();

	animations->Remove(INTRO_SIMON_ANIMATION_1_ID);
	animations->Remove(INTRO_SIMON_ANIMATION_2_ID);
	sprites->Remove(INTRO_SIMON_SPRITE_1_ID);
	sprites->Remove(INTRO_SIMON_SPRITE_2_ID);
	sprites->Remove(INTRO_SIMON_SPRITE_3_ID);
	sprites->Remove(INTRO_SIMON_SPRITE_4_ID);
}

void IntroSimon::Update(DWORD dt)
{
	GameObject::Update(dt);

	x += dx;
	y += dy;
}

void IntroSimon::Render()
{
	animation->Draw(x, y);
}

#pragma endregion
