#include "Scene.h"
#include "..\..\Framework\Sprite.h"
#include "..\..\Framework\Animation.h"

void Scene::Load()
{
	LPSCENE scene = this;
	Parser::Parse_Scene(&scene);
	loaded = true;
	OutputDebugString(L"[INFO] PlayScene loaded OK\n");
}

void Scene::Unload()
{
	enemies.clear();
	items.clear();
	effects.clear();

	if (tilemap) delete tilemap;
	if (grid) delete grid;
	if (player) delete player;

	Animations::GetInstance()->Clear();
	Sprites::GetInstance()->Clear();
	Sound::GetInstance()->Clear();
	Tilesets::GetInstance()->Clear();
	Textures::GetInstance()->Clear();
}


Scenes* Scenes::_instance = 0;

Scenes* Scenes::GetInstance()
{
	if (!_instance) _instance = new Scenes;
	return _instance;
}

void Scenes::Add(int id, LPSCENE scene)
{
	scenes[id] = scene;
	currentID = id;
}

void Scenes::SwitchScene()
{
	if (switchScene != -1)
	{
		LPSCENE current = scenes[currentID];
		if (current->IsLoaded())
			current->Unload();

		currentID = switchScene;
		current = scenes[currentID];
		current->Load();
		switchScene = -1;
	}
}

void Scenes::NextScene(int id)
{
	switchScene = id;
}


