#include "Scene.h"
#include "TitleScene.h"
#include "IntroScene.h"
#include "GameScene.h"
#include "KonoDioDa.h"
#include "Debug.h"

Scenes* Scenes::_instance = 0;

Scenes* Scenes::GetInstance()
{
	if (!_instance) _instance = new Scenes;
	return _instance;
}

void Scenes::LoadResource()
{
	//scenes.push_back(new TitleScene);
	//scenes.push_back(new KonoDioDa);
	//scenes.push_back(new IntroScene);
	scenes.push_back(new GameScene);
	scenes.push_back(NULL);

	currentScene = 0;
}

void Scenes::Update(DWORD dt)
{
	if (!scenes[currentScene]) return;

	LPSCENE scene = scenes[currentScene];

	if (!scene->IsStarted())
		scene->LoadScene();
	else
	{
		if (scene->IsEnd())
		{
			scene->EndScene();
			scene = scenes[currentScene];
		}
		else scene->Update(dt);
	}
}

void Scenes::Render()
{
	if (!scenes[currentScene]) return;

	LPSCENE scene = scenes[currentScene];

	if (!scene->IsStarted()) return;

	scene->Render();
}