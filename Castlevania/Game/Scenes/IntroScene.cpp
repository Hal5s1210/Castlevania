#include "IntroScene.h"

void IntroScene::LoadScene()
{
	x = 0;
	y = 48;
	keyHandler = 0;
	LoadFromFile(L"Resources\\XML\\IntroScene.xml");

	OutputDebugString(L"[INFO] IntroScene loaded OK\n");
	time = GetTickCount();
	sceneStart = true;
}

void IntroScene::EndScene()
{
	for (LPGAMEOBJECT o : mapObjs)
		delete o;

	Sound::GetInstance()->Clear();
	Textures::GetInstance()->Clear();

	OutputDebugString(L"[INFO] IntroScene ended OK\n");
}

void IntroScene::UpdateScene(DWORD dt)
{
	if (!soundplay)
	{
		Sound::GetInstance()->Play(SOUND_INTRO_ID);
		soundplay = true;
	}

	for (LPGAMEOBJECT o : mapObjs)
		o->Update(dt);

	if (GetTickCount() - time >= 7000)
	{
		sceneEnd = true;
		Scenes::GetInstance()->NextScene();
	}
}

void IntroScene::RenderScene()
{
	for (LPGAMEOBJECT o : mapObjs)
		o->Render(x, y);
}

