#include "Scene.h"
#include "TitleScene.h"
#include "IntroScene.h"
#include "Debug.h"

Scenes* Scenes::_instance = 0;

Scenes* Scenes::GetInstance()
{
	if (!_instance) _instance = new Scenes;
	return _instance;
}

void Scenes::LoadResource()
{
	Textures* textures = Textures::GetInstance();
	textures->Add(TITLE_SCENE_TEX_ID, TITLE_SCENE_DIR, D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(INTRO_SCENE_TEX_ID, INTRO_SCENE_DIR, D3DCOLOR_XRGB(255, 255, 255));

	scenes.push_back(new TitleScene);
	scenes.push_back(new IntroScene);
	scenes.push_back(NULL);

	currentScene = 0;
}

void Scenes::Update(DWORD dt)
{
	if (!scenes[currentScene]) return;

	LPSCENE scene = scenes[currentScene];

	if (scene->IsEnd())
	{
		scene->EndScene();
		scene = scenes[currentScene];
		if (scene == NULL) return;
	}

	if (!scene->IsStarted())
		scene->LoadScene();

	scene->Update(dt);
}

void Scenes::Render()
{
	if (!scenes[currentScene]) return;

	scenes[currentScene]->Render();
}