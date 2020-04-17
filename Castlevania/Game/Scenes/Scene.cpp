#include "Scene.h"
#include "..\..\Framework\Sprite.h"
#include "..\..\Framework\Animation.h"

void Scene::Load()
{
	LoadFromFile();
	loaded = true;
	OutputDebugString(L"[INFO] PlayScene loaded OK\n");
}

void Scene::Unload()
{
	Textures::GetInstance()->Clear();
	Sound::GetInstance()->Clear();
	Sprites::GetInstance()->Clear();
	Animations::GetInstance()->Clear();
	Tilesets::GetInstance()->Clear();

	if (tilemap) delete tilemap;
	if (grid) delete grid;
	//if (player) delete player;
}

void Scene::LoadFromFile()
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(filePath);
	if (!result)
	{
		OutputDebugString(L"[ERROR] Load Scene file failed\n");
		return;
	}

	pugi::xml_node root = doc.child(L"Scene");

	Parser::Parse_Texture(root.child(L"Textures"));
	Parser::Parse_Sound(root.child(L"Sounds"));
	Parser::Parse_Object(root.child(L"Objects"));
	Parser::Parse_Player(&player, root.child(L"Player"));
	Parser::Parse_Tileset(root.child(L"Tilesets"));
	Parser::Parse_Tilemap(&tilemap, root.child(L"Map"));
	Parser::Parse_Grid(&grid, root.child(L"Grid"));

	OutputDebugString(L"[ERROR] Load Scene file done\n");
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


