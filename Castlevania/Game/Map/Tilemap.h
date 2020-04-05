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
	std::vector<std::vector<int>> mapMatrix;

	void LoadMatrix(pugi::xml_node node);
	std::vector<int> split(const std::string& s, char delimiter);

public:
	void LoadMap(pugi::xml_node node);
	void Render(float x = 0, float y = 0);
};
