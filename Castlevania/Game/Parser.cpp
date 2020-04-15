#include "Parser.h"

#include <locale>
#include <codecvt>

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

			LPSPRITE s = Sprites::GetInstance()->Get(sprite_id);
			Animation::Frame* f = new Animation::Frame(s, time);
			ani->AddFrame(f);
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

		Parser::Parse_Sprite(root.child(L"Sprites"));
		Parser::Parse_Animation(root.child(L"Animations"));

		std::wstring nodeName = node.name();
		if (nodeName == L"Object")
		{
			Spawner::GetInstance()->CreateObjectSpawner(id);
			LPGAMEOBJECT obj = Spawner::GetInstance()->GetObjectSpawner(id);
			Parser::Parse_AnimationSet(obj, root.child(L"AnimationSet"));
		}
		else if (nodeName == L"Effect")
		{
			Spawner::GetInstance()->CreateEffectSpawner(id);
			LPEFFECT eff = Spawner::GetInstance()->GetEffectSpawner(id);
			Parser::Parse_AnimationSet(eff, root.child(L"AnimationSet"));
		}
		else if (nodeName == L"Item")
		{
			Spawner::GetInstance()->CreateItemSpawner(id);
			LPITEM item = Spawner::GetInstance()->GetItemSpawner(id);
			Parser::Parse_AnimationSet(item, root.child(L"AnimationSet"));
		}
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


void Parser::Parse_Player(Simon** player, pugi::xml_node root)
{
	LPCWSTR path = root.child(L"Resource").attribute(L"path").value();
	pugi::xml_document doc;
	pugi::xml_parse_result result;

	result = doc.load_file(path);
	if (!result) return;

	pugi::xml_node node = doc.child(L"Object");

	Parser::Parse_Sprite(node.child(L"Sprites"));
	Parser::Parse_Animation(node.child(L"Animations"));
	
	(*player) = new Simon;

	Parser::Parse_Whip((*player)->GetWhip(), root.child(L"Whip"));

	Parser::Parse_SubWeapon((*player)->GetSubWeapon(), root.child(L"SubWeapon"));

	Parser::Parse_AnimationSet((*player), node.child(L"AnimationSet"));
	
	float x = root.child(L"Position").attribute(L"x").as_int();
	float y = root.child(L"Position").attribute(L"y").as_int();

	(*player)->SetPosition(x, y);

}

void Parser::Parse_Whip(Whip* whip, pugi::xml_node root)
{
	LPCWSTR path = root.attribute(L"path").value();
	pugi::xml_document doc;
	pugi::xml_parse_result result;

	result = doc.load_file(path);
	if (!result) return;

	pugi::xml_node node = doc.child(L"Object");

	Parser::Parse_Sprite(node.child(L"Sprites"));
	Parser::Parse_Animation(node.child(L"Animations"));
	Parser::Parse_AnimationSet(whip, node.child(L"AnimationSet"));
}

void Parser::Parse_SubWeapon(SubWeapon* sub, pugi::xml_node root)
{
	for (pugi::xml_node weapon : root)
	{
		LPCWSTR path = weapon.attribute(L"path").value();
		pugi::xml_document doc;
		pugi::xml_parse_result result;

		result = doc.load_file(path);
		if (!result) return;


		pugi::xml_node node = doc.child(L"Object");

		Parser::Parse_Sprite(node.child(L"Sprites"));
		Parser::Parse_Animation(node.child(L"Animations"));
		std::wstring name = weapon.name();
		if (name == L"Dagger")
		{
			Parser::Parse_AnimationSet(sub->GetDagger(), node.child(L"AnimationSet"));
		}
	}
}



void Parser::Parse_Tileset(pugi::xml_node root)
{
	for (pugi::xml_node set : root)
	{
		int id = set.attribute(L"id").as_int();
		int textureid = set.attribute(L"texture").as_int();
		int tileW = set.attribute(L"tileW").as_int();
		int tileH = set.attribute(L"tileH").as_int();

		Tilesets::GetInstance()->Add(id, textureid, tileW, tileH);
	}
}

void Parser::Parse_Tilemap(Tilemap** tilemap, pugi::xml_node root)
{
	if (!root) return;

	pugi::xml_node map = root.child(L"Map");

	int id = map.attribute(L"tileset").as_int();

	LPTILESET tileset = Tilesets::GetInstance()->Get(id);

	int w = map.attribute(L"width").as_int();
	int h = map.attribute(L"height").as_int();
	int tileW = map.attribute(L"tileW").as_int();
	int tileH = map.attribute(L"tileH").as_int();

	(*tilemap) = new Tilemap(tileset, w, h, tileW, tileH);
	std::vector<std::vector<int>>* mx = new std::vector<std::vector<int>>;
	Parser::Parse_TilemapMatrix(mx, map.child(L"Matrix"));
	(*tilemap)->SetMatrix(mx);
}

void Parser::Parse_TilemapMatrix(std::vector<std::vector<int>>* matrix, pugi::xml_node root)
{
	using convert_type = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_type, wchar_t> converter;

	for (pugi::xml_node r : root)
	{
		std::wstring str = r.text().as_string();
		std::string converted_str = converter.to_bytes(str);
		std::vector<int> row = Parser::split(converted_str, ',');
		matrix->push_back(row);
	}
}

std::vector<int> Parser::split(const std::string& s, char delimiter)
{
	std::vector<int> out;
	std::stringstream ss(s);

	std::string item;

	while (std::getline(ss, item, delimiter))
	{
		out.push_back(std::stoi(item));
	}

	return out;
}


void Parser::Parse_Grid(Grid** grid, pugi::xml_node root)
{
	if (!root) return;

	int w = root.attribute(L"width").as_int();
	int h = root.attribute(L"height").as_int();
	int cellW = root.attribute(L"cellW").as_int();
	int cellH = root.attribute(L"cellH").as_int();

	(*grid) = new Grid(w, h, cellW, cellH);
	Parser::Parse_Cell((*grid)->GetCells(), root);
}

void Parser::Parse_Cell(std::vector<std::vector<std::vector<LPGAMEOBJECT>>>* cells, pugi::xml_node root)
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
			int item = obj.attribute(L"item").as_int();

			LPGAMEOBJECT o = Spawner::GetInstance()->SpawnObject(id, x, y, item);
			cells->at(i).at(j).push_back(o);
		}
	}
}