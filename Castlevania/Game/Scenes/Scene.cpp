#include "Scene.h"
#include "..\..\Framework\Sprite.h"
#include "..\..\Framework\Animation.h"


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
	Parser::Parse_Tilemap(&tilemap, root.child(L"Tilemap"));
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


void Scenes::NextScene(int id)
{
	LPSCENE current = scenes[currentID];
	if (current->IsLoaded())
		current->Unload();

	current = scenes[id];
	current->Load();
}


