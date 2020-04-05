#pragma once

#include <vector>
#include "..\Objects\GameObject.h"
#include "..\..\Dependencies\pugixml\src\pugixml.hpp"

class Grid
{
private:
	int width;
	int height;
	int cellWidth;
	int cellHeight;
	std::vector<std::vector<std::vector<LPGAMEOBJECT>>> cells;

public:
	void Grid_Init(pugi::xml_node node);
	void GetObjectlist(std::vector<LPGAMEOBJECT>* list);

};

