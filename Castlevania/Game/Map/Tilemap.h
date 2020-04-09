#pragma once

#include <vector>
#include <sstream>
#include "..\..\Dependencies\pugixml\src\pugixml.hpp"
#include "Tileset.h"

class Tilemap
{
private:
	LPTILESET tileset;
	int tileW;
	int tileH;
	int width;
	int height;
	std::vector<std::vector<int>> matrix;

public:
	Tilemap(LPTILESET tileset, int w, int h, int tw, int th) :
		tileset(tileset), width(w), height(h), tileW(tw), tileH(th) {}

	std::vector<std::vector<int>>* GetMatrix() { return &matrix; }

	void Render(float x = 0, float y = 0);
};
