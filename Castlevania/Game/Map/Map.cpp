#include "Map.h"
#include <locale>
#include <codecvt>

void Map::LoadMap(pugi::xml_node mapNode)
{
	pugi::xml_node info = mapNode.child(L"MapInfo");
	if (!info) return;

	int id = info.attribute(L"tileset").as_int();
	tileW = info.attribute(L"tileW").as_int();
	height = info.attribute(L"height").as_int();
	width = info.attribute(L"width").as_int();
	tileH = info.attribute(L"tileH").as_int();

	tileset = Textures::GetInstance()->Get(id);

	LoadTiles();
	LoadMatrix(mapNode.child(L"Matrix"));
	LoadCollisionTile(mapNode.child(L"CollisionTile"));
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

void Map::LoadCollisionTile(pugi::xml_node node)
{
	using convert_type = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_type, wchar_t> converter;
	std::wstring str = node.text().as_string();
	std::string converted_str = converter.to_bytes(str);
	collisionTiles = split(converted_str, ',');
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