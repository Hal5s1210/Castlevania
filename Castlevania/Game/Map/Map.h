#pragma once

#include <vector>
#include <sstream>
#include "..\..\Framework\Texture.h"
#include "..\..\Framework\Viewport.h"
#include "..\..\Framework\Graphics.h"
#include "..\Objects\GameObject.h"
#include "..\..\Dependencies\pugixml\src\pugixml.hpp"

class Map
{
private:
	LPTEXTURE tileset;
	int tileW;
	int tileH;
	int width;
	int height;
	std::vector<std::vector<int>> mapMatrix;
	std::vector<int> collisionTiles;
	std::vector<RECT> tiles;

	void LoadTiles();
	void LoadMatrix(pugi::xml_node node);
	void LoadCollisionTile(pugi::xml_node node);
	std::vector<int> split(const std::string& s, char delimiter);

public:
	void LoadMap(pugi::xml_node node);
	void Render(float x = 0, float y = 0);
};
