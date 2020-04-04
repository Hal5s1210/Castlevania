#pragma once

#include "..\..\Framework\Texture.h"

class Tileset
{
private:
	LPTEXTURE texture;
	int tileWidth;
	int tileHeight;
	std::vector<RECT> tiles;

public:
	Tileset(LPTEXTURE texture, int w, int h);

	void LoadTiles();
	void Draw(int id, float x, float y, int alpha = 255, bool flip = false);

};

typedef Tileset* LPTILESET;


class Tilesets
{
private:
	static Tilesets* _instance;

	std::unordered_map<int, LPTILESET> tilesets;

public:
	static Tilesets* GetInstance();

	void Add(int id, int texture_id, int w, int h);
	void Remove(int id);
	void Clear();
	LPTILESET Get(int id) { return tilesets[id]; }

};

