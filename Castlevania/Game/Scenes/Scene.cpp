#include "Scene.h"


void Scene::Update(DWORD dt)
{
	if (sceneStart && sceneEnd) return;

	if (!sceneStart)
		LoadScene();
	else 
	{
		if (!sceneEnd)
		{
			UpdateScene(dt);
		}
		else
		{
			EndScene();
		}
	}
}

void Scene::Render()
{
	if (sceneStart && !sceneEnd)
		RenderScene();
}

void Scene::LoadFromFile(const wchar_t* filepath)
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(filepath);
	if (!result)
	{
		OutputDebugString(L"[ERROR] Load TitleScene texture failed\n");
		sceneStart = false;
		sceneEnd = true;
		return;
	}

	pugi::xml_node root = doc.child(L"Scene");

	// Load Texture
	//
	pugi::xml_node textureNode = root.child(L"Textures");
	for (pugi::xml_node node : textureNode)
	{
		int id = node.attribute(L"Id").as_int();
		LPCWSTR path = path = node.attribute(L"path").value();
		int r = node.attribute(L"red").as_int();
		int g = node.attribute(L"green").as_int();
		int b = node.attribute(L"blue").as_int();

		Textures::GetInstance()->Add(id, path, D3DCOLOR_XRGB(r, g, b));
	}

	OutputDebugString(L"[INFO] Load Scene texture done\n");

	// Load Sound
	//
	pugi::xml_node soundNode = root.child(L"Sounds");
	for (pugi::xml_node node : soundNode)
	{
		int id = node.attribute(L"Id").as_int();
		LPCWSTR path = node.attribute(L"path").value();

		Sound::GetInstance()->Load(id, path);
	}

	OutputDebugString(L"[INFO] Load Scene sound done\n");

	// Load Player
	//
	pugi::xml_node playerNode = root.child(L"Player");
	if (playerNode)
	{
		int id = playerNode.attribute(L"Id").as_int();

		LPGAMEOBJECT o = Generator::PlayerCreate();

		float x, y;
		x = playerNode.child(L"Position").attribute(L"x").as_float();
		y = playerNode.child(L"Position").attribute(L"y").as_float();
		o->SetPosition(x, y);

		float vx, vy;
		vx = playerNode.child(L"Speed").attribute(L"x").as_float();
		vy = playerNode.child(L"Speed").attribute(L"y").as_float();
		o->SetSpeed(vx, vy);

		player = o;
	}

	OutputDebugString(L"[INFO] Load Scene player done\n");

	// Load Map
	//
	pugi::xml_node mapNode = root.child(L"Map");
	if (mapNode)
	{
		map = new Map;
		map->LoadMap(mapNode);

		// Load Object
		//
		pugi::xml_node objectNode = mapNode.child(L"Objects");
		for (pugi::xml_node node : objectNode)
		{
			int id = node.attribute(L"Id").as_int();

			LPGAMEOBJECT o = Generator::ObjectCreate(id);

			int x, y;
			x = node.child(L"Position").attribute(L"x").as_int();
			y = node.child(L"Position").attribute(L"y").as_int();
			o->SetPosition(x, y);

			float vx, vy;
			vx = node.child(L"Speed").attribute(L"x").as_float();
			vy = node.child(L"Speed").attribute(L"y").as_float();
			o->SetSpeed(vx, vy);

			mapObjs.push_back(o);
		}

	}

	OutputDebugString(L"[INFO] Load Scene map done\n");

	OutputDebugString(L"[INFO] Load Scene object done\n");

}



Scenes* Scenes::_instance = 0;

Scenes* Scenes::GetInstance()
{
	if (!_instance) _instance = new Scenes;
	return _instance;
}

void Scenes::Add(LPSCENE scene)
{
	scenes.push_back(scene);
	currentScene = 0;
}


