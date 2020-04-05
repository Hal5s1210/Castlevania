#include "Parser.h"
#include "..\Framework\Texture.h"
#include "..\Framework\Sprite.h"
#include "..\Framework\Animation.h"
#include "..\Framework\Sound.h"
#include "Objects/Spawner.h"

void Parser::Parse_Texture(pugi::xml_node root)
{
	for (pugi::xml_node node : root)
	{
		int id = node.attribute(L"id").as_int();

		if (Textures::GetInstance()->Get(id) != NULL) continue;

		LPCWSTR path = path = node.attribute(L"path").value();
		int r = node.attribute(L"red").as_int();
		int g = node.attribute(L"green").as_int();
		int b = node.attribute(L"blue").as_int();

		Textures::GetInstance()->Add(id, path, D3DCOLOR_XRGB(r, g, b));
	}
}

void Parser::Parse_Sprite(pugi::xml_node root)
{
	for (pugi::xml_node node : root)
	{
		int id = node.attribute(L"id").as_int();

		if (Sprites::GetInstance()->Get(id) != NULL) continue;

		int texture_id = node.attribute(L"texture").as_int();
		int x = node.attribute(L"x").as_int();
		int y = node.attribute(L"y").as_int();
		int w = node.attribute(L"w").as_int();
		int h = node.attribute(L"h").as_int();

		Sprites::GetInstance()->Add(id, new Sprite(id, texture_id, x, y, w, h));
	}
}

void Parser::Parse_Animation(pugi::xml_node root)
{
	for (pugi::xml_node node : root)
	{
		int id = node.attribute(L"id").as_int();

		if (Animations::GetInstance()->Get(id) != NULL) continue;

		LPANIMATION ani = new Animation;
		for (pugi::xml_node frame : node)
		{
			int sprite_id = frame.attribute(L"sprite").as_int();
			int time = frame.attribute(L"time").as_int();

			ani->AddFrame(sprite_id, time);
		}

		Animations::GetInstance()->Add(id, ani);
	}
}

void Parser::Parse_Sound(pugi::xml_node root)
{
	for (pugi::xml_node node : root)
	{
		int id = node.attribute(L"id").as_int();
		LPCWSTR path = node.attribute(L"path").value();

		Sound::GetInstance()->Load(id, path);
	}
}

void Parser::Parse_Object(pugi::xml_node root)
{
	for (pugi::xml_node node : root)
	{
		int id = node.attribute(L"type").as_int();
		LPCWSTR path = node.attribute(L"path").value();

		pugi::xml_document doc;
		pugi::xml_parse_result result = doc.load_file(path);
		if (!result) continue;

		pugi::xml_node root = doc.child(L"Object");

		Parser::Parse_Texture(root.child(L"Textures"));
		Parser::Parse_Sprite(root.child(L"Sprites"));
		Parser::Parse_Animation(root.child(L"Animations"));

		Spawner::GetInstance()->CreateObjectSpawner(id, root.child(L"AnimationSet"));
	}
}

void Parser::Parse_AnimationSet(LPGAMEOBJECT obj, pugi::xml_node root)
{
	for (pugi::xml_node node : root)
	{
		int animation_id = node.attribute(L"id").as_int();
		LPANIMATION ani = Animations::GetInstance()->Get(animation_id);
		obj->AddAnimation(ani);
	}
}

void Parser::Parse_Grid(std::vector<std::vector<std::vector<LPGAMEOBJECT>>>* cells, pugi::xml_node root)
{
	for (pugi::xml_node cell : root)
	{
		int i = cell.attribute(L"row").as_int();
		int j = cell.attribute(L"column").as_int();

		for (pugi::xml_node obj : cell)
		{
			int id = obj.attribute(L"type").as_int();
			float x = obj.attribute(L"x").as_float();
			float y = obj.attribute(L"y").as_float();

			LPGAMEOBJECT o = Spawner::GetInstance()->SpawnObject(id);
			o->SetPosition(x, y);

			cells->at(i).at(j).push_back(o);
		}
	}
}
