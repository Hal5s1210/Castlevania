#include "Map.h"
#include <locale>
#include <codecvt>

void Map::LoadMap(pugi::xml_node node)
{
	int id = node.attribute(L"tileset").as_int();
	tileset = Textures::GetInstance()->Get(id);
	tileW = node.attribute(L"tileW").as_int();
	height = node.attribute(L"height").as_int();
	width = node.attribute(L"width").as_int();
	tileH = node.attribute(L"tileH").as_int();

	LoadTiles();
	LoadMatrix(node.child(L"Matrix"));
	
}

void Map::Render(float sx, float sy)
{
	Graphics* g = Graphics::GetInstance();
	Viewport* view = Viewport::GetInstance();

	float cam_x, cam_y;
	view->GetPosition(cam_x, cam_y);
	int cam_w, cam_h;
	view->GetSize(cam_w, cam_h);

	int X = max(cam_x / tileW, 0);
	int Y = max(cam_y / tileH, 0);
	int XW = min((cam_x + cam_w) / tileW + 1, width);
	int YH = min((cam_y + cam_h) / tileH + 1, height);


	for (int i = Y; i < YH; i++)
	{
		for (int j = X; j < XW; j++)
		{
			int id = mapMatrix[i][j];
			g->Draw(j * tileW + sx, i * tileH + sy, tileset, tiles[id - 1]);
		}
	}
}

void Map::LoadTiles()
{
	int w = tileset->GetInfo().Width / tileW;
	int h = tileset->GetInfo().Height / tileH;
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			RECT r;
			r.left = j * tileW;
			r.top = i * tileH;
			r.right = r.left + tileW;
			r.bottom = r.top + tileH;

			tiles.push_back(r);
		}
	}
}

void Map::LoadMatrix(pugi::xml_node node)
{
	using convert_type = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_type, wchar_t> converter;

	for(pugi::xml_node n : node)
	{
		std::wstring str = n.text().as_string();
		std::string converted_str = converter.to_bytes(str);
		std::vector<int> row = split(converted_str, ',');
		mapMatrix.push_back(row);
	}
}

std::vector<int> Map::split(const std::string& s, char delimiter)
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

void Map::GetMapObject(pugi::xml_node node, std::vector<LPGAMEOBJECT>* objlist)
{
	pugi::xml_node objects = node.child(L"MapObjects");
	for (pugi::xml_node n : objects)
	{
		Platform* p = new Platform;

		float x, y;
		x = n.child(L"Position").attribute(L"x").as_float();
		y = n.child(L"Position").attribute(L"y").as_float();
		p->SetPosition(x, y);

		float w, h;
		w = n.child(L"Size").attribute(L"w").as_int();
		h = n.child(L"Size").attribute(L"h").as_int();
		p->SetBoundSize(w, h);

		objlist->push_back(p);
	}
}

