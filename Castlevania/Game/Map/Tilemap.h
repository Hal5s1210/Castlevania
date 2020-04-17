#pragma once

#include <vector>
#include <sstream>
#include "..\..\Dependencies\pugixml\src\pugixml.hpp"
#include "Tileset.h"

class Tilemap
{
public:;

private:
	LPTILESET tileset;
	int width;
	int height;
	int tileW;
	int tileH;
	std::vector<std::vector<int>>* matrix;
	int currentArea;
	std::vector<RECT> areas;

public:
	Tilemap(LPTILESET tileset, int w, int h, int tw, int th) :
		tileset(tileset), width(w), height(h), tileW(tw), tileH(th) {}

	void SetMatrix(std::vector<std::vector<int>>* matrix) { this->matrix = matrix; }
	void SetArea(int i) { currentArea = i; }
	void AddArea(RECT rect) { areas.push_back(rect); }
	RECT GetAreaRect() { return areas[currentArea]; }
	void Render(float x = 0, float y = 0);
};
