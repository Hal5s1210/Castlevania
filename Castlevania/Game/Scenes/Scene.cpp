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
	for (LPENEMY e : enemies)
		e->Unactive();
	enemies.clear();

	for (LPITEM i : items)
		delete i;
	items.clear();

	for (LPEFFECT e : effects)
		delete e;
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

void Scene::Reset()
{
	for (LPENEMY e : enemies)
		e->Unactive();
	enemies.clear();

	for (LPITEM i : items)
		delete i;
	items.clear();

	for (LPEFFECT e : effects)
		delete e;
	effects.clear();

	grid->GetObjectlist(&objects);
	objects.push_back(player);
	player->Reset();
	tilemap->ResetArea();
}

void Scene::KillAllEnemies()
{
	for (LPENEMY e : enemies)
	{
		if (e->IsAlive())
			e->TakeDamage(999, NULL);
	}
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
	if (switchScene != -999)
	{
		LPSCENE current = scenes[currentID];
		if (current->IsLoaded())
			current->Unload();

		currentID = switchScene;
		current = scenes[currentID];
		Viewport::GetInstance()->SetAuto(false);
		current->Load();
		switchScene = -999;
	}
}

void Scenes::NextScene(int id)
{
	switchScene = id;
}