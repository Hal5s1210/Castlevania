#include "IntroScene.h"
#include "..\Objects\ObjectGenerator.h"


void IntroScene::LoadScene()
{
	keyHandler = 0;
	id = INTRO_SCENE_ID;
	
	generator = ObjectGenerator::GetInstance();
	LoadFromFile(L"Resources\\XML\\IntroScene.xml");

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
}

void IntroScene::UpdateScene(DWORD dt)
{
	for (LPGAMEOBJECT o : mapObjs)
		o->Update(dt);

	if (GetTickCount() - time >= 7000)
		sceneEnd = true;
}

void IntroScene::RenderScene()
{
	for (LPGAMEOBJECT o : mapObjs)
		o->Render();
}

