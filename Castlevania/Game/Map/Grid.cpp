#include "Grid.h"
#include "..\Objects\Spawner.h"
#include "..\Parser.h"
#include "..\..\Framework\Viewport.h"
#include "..\Scenes\Scene.h"

Grid::Grid(int w, int h, int cw, int ch) :
	width(w), height(h), cellWidth(cw), cellHeight(ch)
{
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
}

Grid::~Grid()
{
	for (int i = 0; i < cells.size(); i++)
	{
		for (int j = 0; j < cells[i].size(); j++)
		{
			for (LPGAMEOBJECT o : cells[i][j])
			{
				delete o;
			}
			cells[i][j].clear();
		}
		cells[i].clear();
	}
	cells.clear();
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
	int W = min(ceil((cam_x + cam_w) / cellWidth), width);
	int H = min(ceil((cam_y + cam_h) / cellHeight), height);

	for (int i = Y; i < H; i++)
	{
		for (int j = X; j < W; j++)
		{
			for (LPGAMEOBJECT o : cells[i][j])
			{
				if (dynamic_cast<LPENEMY>(o))
				{
					LPENEMY e = dynamic_cast<LPENEMY>(o);
					if (!e->IsActive())
					{
						e->Active();
						Scenes::GetInstance()->GetScene()->AddEnemy(e);
					}
					else
					{
						e->InCell(true);
					}
				}
				if (dynamic_cast<Candle*>(o))
				{
					if(dynamic_cast<Candle*>(o)->IsAlive())
						list->push_back(o);						
				}
				if (dynamic_cast<Portal*>(o))
				{
					if(dynamic_cast<Portal*>(o)->IsActive())
						list->push_back(o);
				}
				else
				{
					list->push_back(o);
				}
			}
		}
	}
}