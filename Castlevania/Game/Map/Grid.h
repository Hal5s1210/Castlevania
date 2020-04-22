#pragma once

#include <vector>
#include "..\Objects\GameObject.h"

class Grid
{
private:
	int width;
	int height;
	int cellWidth;
	int cellHeight;
	std::vector<std::vector<std::vector<LPGAMEOBJECT>>> cells;

public:
	Grid(int w, int h, int cw, int ch);
	~Grid();

	std::vector<std::vector<std::vector<LPGAMEOBJECT>>>* GetCells() { return &cells; }

	void GetObjectlist(std::vector<LPGAMEOBJECT>* list);

};

