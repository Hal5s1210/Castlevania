#include "Scene.h"
#include "Debug.h"


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
		else EndScene();
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
		sceneStart = true;
		sceneEnd = true;
		return;
	}

	// Load Texture
	//
	pugi::xml_node textureNode = doc.child(L"Textures");
	for (pugi::xml_node node : textureNode)
	{
		int id = std::stoi(node.attribute(L"Id").value());
		LPCWSTR path = node.child_value(L"Path");

		Textures::GetInstance()->Add(id, path, D3DCOLOR_XRGB(0, 128, 0));
	}

	OutputDebugString(L"[INFO] Load Scene texture done\n");

	// Load Sound
	//
	pugi::xml_node soundNode = doc.child(L"Sounds");
	for (pugi::xml_node node : soundNode)
	{
		int id = std::stoi(node.attribute(L"Id").value());
		LPCWSTR path = node.child_value(L"Path");

		Sound::GetInstance()->Load(id, path);
	}

	OutputDebugString(L"[INFO] Load Scene sound done\n");

	// Load Object
	//
	pugi::xml_node objectNode = doc.child(L"Objects");
	for (pugi::xml_node node : objectNode)
	{
		int id = std::stoi(node.attribute(L"Id").value());

		LPGAMEOBJECT o = generator->ObjectCreate(id);

		int x, y;
		x = std::stoi(node.child_value(L"X"));
		y = std::stoi(node.child_value(L"Y"));
		o->SetPosition(x, y);

		mapObjs.push_back(o);
	}

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


