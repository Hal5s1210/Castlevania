#include "IntroScene.h"
#include "Simon.h"
#include "Sound.h"

void IntroScene::LoadScene()
{
	id = INTRO_SCENE_ID;
	Textures::GetInstance()->Add(INTRO_BG_TEX_ID, INTRO_BG_TEX_DIR, D3DCOLOR_XRGB(255, 255, 255));
	Textures::GetInstance()->Add(INTRO_BAT_TEX_ID, INTRO_BAT_TEX_DIR, D3DCOLOR_XRGB(116, 116, 116));
	Textures::GetInstance()->Add(INTRO_CLOUD_TEX_ID, INTRO_CLOUD_TEX_DIR, D3DCOLOR_XRGB(116, 116, 116));
	Textures::GetInstance()->Add(SIMON_TEX_ID, SIMON_TEX_DIR, D3DCOLOR_XRGB(116, 116, 116));

	LPSOUND sound = Sound::GetInstance();
	sound->Load(INTRO_SONG_ID, INTRO_SONG_DIR);
	sound->Play(INTRO_SONG_ID);

	bg = new IntroBG;
	bg->SetPosition(0, 48);
	mapObjs.push_back(bg);

	bat1 = new IntroBat;
	bat1->SetPosition(30, 108);
	bat1->SetSpeed(0.01, -0.007);
	mapObjs.push_back(bat1);

	bat2 = new IntroBat;
	bat2->SetPosition(160, 74);
	bat2->SetSpeed(-0.006, 0);
	mapObjs.push_back(bat2);

	cloud = new IntroCloud;
	cloud->SetPosition(240, 76);
	cloud->SetSpeed(-0.006, 0);
	mapObjs.push_back(cloud);

	simon = new IntroSimon;
	simon->SetPosition(240, 177);
	simon->SetSpeed(-0.03, 0);
	mapObjs.push_back(simon);

	OutputDebugString(L"[INFO] IntroScene loaded OK\n");
	time = GetTickCount();
	sceneStart = true;
}

void IntroScene::EndScene()
{
	for (LPGAMEOBJECT o : mapObjs)
		delete o;

	Sound::GetInstance()->Remove(INTRO_SONG_ID);

	Textures::GetInstance()->Remove(INTRO_BG_TEX_ID);
	Textures::GetInstance()->Remove(INTRO_BAT_TEX_ID);
	Textures::GetInstance()->Remove(INTRO_CLOUD_TEX_ID);
	Textures::GetInstance()->Remove(SIMON_TEX_ID);

	OutputDebugString(L"[INFO] IntroScene ended OK\n");
	Scenes::GetInstance()->NextScene();
}

void IntroScene::Update(DWORD dt)
{
	float x, y;

	bat2->GetPosition(x, y);
	if (x <= 128)
		bat2->SetSpeed(-0.0015, -0.004);

	for (LPGAMEOBJECT o : mapObjs)
		o->Update(dt);

	if (GetTickCount() - time >= 7000)
		sceneEnd = true;
}

void IntroScene::Render()
{
	for (LPGAMEOBJECT o : mapObjs)
		o->Render();
}




#pragma region IntroBG

IntroBG::IntroBG()
{
	LPTEXTURE texture = Textures::GetInstance()->Get(INTRO_BG_TEX_ID);

	LPANIMATION s = new Animation(texture);
	s->AddFrame(0, 0, 256, 192);
	AddAnimation(s);

	SetState(INTRO_BG_ANIMATION);
}

IntroBG::~IntroBG()
{
	animations.clear();
}

void IntroBG::Render()
{
	animations[currentAnimation]->Draw(x, y);
}

#pragma endregion




#pragma region IntroBat

IntroBat::IntroBat()
{
	LPTEXTURE texture = Textures::GetInstance()->Get(INTRO_BAT_TEX_ID);

	LPANIMATION s = new Animation(texture);
	s->AddFrame(0, 0, 8, 8);
	s->AddFrame(8, 0, 8, 8);
	AddAnimation(s);

	SetAnimation(INTRO_BAT_ANIMATION);
}

IntroBat::~IntroBat()
{
	animations.clear();
}

void IntroBat::Update(DWORD dt)
{
	GameObject::Update(dt);

	x += dx;
	y += dy;
}

void IntroBat::Render()
{
	animations[currentAnimation]->Draw(x, y);
}

#pragma endregion




#pragma region IntroCould

IntroCloud::IntroCloud()
{
	LPTEXTURE texture = Textures::GetInstance()->Get(INTRO_CLOUD_TEX_ID);

	LPANIMATION s = new Animation(texture);
	s->AddFrame(0, 0, 32, 16);
	AddAnimation(s);

	SetAnimation(INTRO_CLOUD_ANIMATION);
}

IntroCloud::~IntroCloud()
{
	animations.clear();
}

void IntroCloud::Update(DWORD dt)
{
	GameObject::Update(dt);

	x += dx;
	y += dy;
}

void IntroCloud::Render()
{
	animations[currentAnimation]->Draw(x, y);
}
#pragma endregion




#pragma region IntroSimon

IntroSimon::IntroSimon()
{
	LPTEXTURE texture = Textures::GetInstance()->Get(SIMON_TEX_ID);

	LPANIMATION s1 = new Animation(texture);
	s1->AddFrame(0, 0, 16, 32);
	s1->AddFrame(0, 32, 16, 32);
	s1->AddFrame(16, 32, 16, 32);
	s1->AddFrame(0, 32, 16, 32);
	AddAnimation(s1);

	LPANIMATION s2 = new Animation(texture);
	s2->AddFrame(80, 0, 16, 32);
	AddAnimation(s2);

	SetAnimation(INTRO_SIMON_ANIMATION_1);
}
IntroSimon::~IntroSimon()
{
	animations.clear();
}

void IntroSimon::Update(DWORD dt)
{
	if (x < 120)
	{
		SetAnimation(INTRO_SIMON_ANIMATION_2);
		SetSpeed(0, 0);
		SetPosition(120, 177);
	}

	GameObject::Update(dt);

	x += dx;
	y += dy;
}

void IntroSimon::Render()
{
	animations[currentAnimation]->Draw(x, y);
}

#pragma endregion
