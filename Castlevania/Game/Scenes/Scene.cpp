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
	Parser::Parse_Sprite(root.child(L"Sprites"));
	Parser::Parse_Animation(root.child(L"Animations"));
	Parser::Parse_Sound(root.child(L"Sounds"));
	Parser::Parse_Object(root.child(L"Objects"));

	tilemap = new Tilemap;
	tilemap->LoadMap(root.child(L"Tilemap"));

	grid = new Grid;
	grid->Grid_Init(root.child(L"Grid"));

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
	currentScene = id;
}


