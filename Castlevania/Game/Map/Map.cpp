#include "Map.h"
#include <locale>
#include <codecvt>

Map::~Map()
{
	for (int i = 0; i < height; i++)
		delete[] mapMatrix[i];
	delete[] mapMatrix;
}

void Map::LoadMap(pugi::xml_node node)
{
	int id = node.attribute(L"tileset").as_int();
	tileset = Textures::GetInstance()->Get(id);
	tileW = node.attribute(L"tileW").as_int();
	height = node.attribute(L"height").as_int();
	width = node.attribute(L"width").as_int();
	tileH = node.attribute(L"tileH").as_int();

	LoadTiles();
	LoadCollisionTiles(node.child(L"CollisionTiles"));
	LoadMatrix(node.child(L"Matrix"));
	
}

void Map::Render(float sx, float sy)
{
	Graphics* g = Graphics::GetInstance();
	Viewport* view = Viewport::GetInstance();
	float x, y;
	view->GetPosition(x, y);
	int w, h;
	view->GetSize(w, h);
	int X, Y, XW, YH;
	X = max(x / tileW, 0);
	Y = max(y / tileH, 0);
	XW = min((x + w) / tileW + 1, width);
	YH = min((y + h) / tileH + 1, height);


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

void Map::LoadCollisionTiles(pugi::xml_node node)
{
	using convert_type = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_type, wchar_t> converter;
	std::wstring str = node.text().as_string();
	std::string converted_str = converter.to_bytes(str);
	collisionTiles = split(converted_str, ',');
}

void Map::LoadMatrix(pugi::xml_node node)
{
	mapMatrix = new int* [height];
	for (int i = 0; i < height; i++)
		mapMatrix[i] = new int[width];

	int i = 0, j = 0;
	using convert_type = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_type, wchar_t> converter;
	for(pugi::xml_node n : node)
	{
		std::wstring str = n.text().as_string();
		std::string converted_str = converter.to_bytes(str);

		std::vector<int> substr = split(converted_str, ',');

		for (int s : substr)
		{
			mapMatrix[i][j] = s;
			j++;
			if (j == width)
			{
				j = 0;
				i++;
			}
		}
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

void Map::GetMapObject(std::vector<LPGAMEOBJECT>* objlist)
{
	std::vector<int>::iterator it;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			it = std::find_if(collisionTiles.begin(), collisionTiles.end(), [&](int& o) { return o == mapMatrix[i][j]; });
			if(it != collisionTiles.end())
			{
				Platform* p = new Platform;
				p->SetBoundSize(tileW, tileH);
				p->SetPosition(j * tileW, i * tileW);

				objlist->push_back(p);
			}
		}
	}
}

