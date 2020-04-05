#include "Grid.h"
#include "..\Objects\Spawner.h"
#include "..\Parser.h"
#include "..\..\Framework\Viewport.h"

void Grid::Grid_Init(pugi::xml_node root)
{
	width = root.attribute(L"").as_int();
	height = root.attribute(L"").as_int();
	cellWidth = root.attribute(L"").as_int();
	cellHeight = root.attribute(L"").as_int();

	for (int i = 0; i < height; i++)
	{
		std::vector<std::vector<LPGAMEOBJECT>> row;
		for (int j = 0; j < width; j++)
		{
			std::vector<LPGAMEOBJECT> objs;
			row.push_back(objs);
		}
		cells.push_back(row);
	}

	Parser::Parse_Grid(&cells, root);
}

void Grid::GetObjectlist(std::vector<LPGAMEOBJECT>* list)
{
	list->clear();
	float cam_x, cam_y;
	int cam_w, cam_h;
	Viewport::GetInstance()->GetPosition(cam_x, cam_y);
	Viewport::GetInstance()->GetSize(cam_w, cam_h);
	int X = max(cam_x / cellWidth, 0);
	int Y = max(cam_y / cellHeight, 0);
	int W = min((cam_x + cam_w) / cellWidth, width);
	int H = min((cam_y + cam_h) / cellHeight, height);

	for (int i = Y; i < H; i++)
	{
		for (int j = W; j < W; j++)
		{
			for (LPGAMEOBJECT o : cells[i][j])
			{
				list->push_back(o);
			}
		}
	}
}