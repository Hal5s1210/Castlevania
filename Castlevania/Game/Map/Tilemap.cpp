#include "Tilemap.h"
#include <locale>
#include <codecvt>
#include "..\..\Framework\Viewport.h"
#include "..\Objects\Others\Block.h"

void Tilemap::LoadMap(pugi::xml_node mapNode)
{
	pugi::xml_node info = mapNode.child(L"Map");
	if (!info) return;

	int id = info.attribute(L"Tileset").as_int();

	tileset = Tilesets::GetInstance()->Get(id);

	width = info.attribute(L"width").as_int();
	height = info.attribute(L"height").as_int();
	tileW = info.attribute(L"tileW").as_int();
	tileH = info.attribute(L"tileH").as_int();

	LoadMatrix(mapNode.child(L"Matrix"));
}

void Tilemap::Render(float sx, float sy)
{
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
			tileset->Draw(id - 1, j * tileW + sx, i * tileH + sy);
		}
	}
}


void Tilemap::LoadMatrix(pugi::xml_node node)
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


std::vector<int> Tilemap::split(const std::string& s, char delimiter)
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