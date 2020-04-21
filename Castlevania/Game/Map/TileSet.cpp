#include "Tileset.h"
#include "..\..\Framework\Graphics.h"

Tileset::Tileset(LPTEXTURE texture, int w, int h)
{
	this->texture = texture;
	tileWidth = w;
	tileHeight = h;
}


void Tileset::LoadTiles()
{
	int w = texture->GetInfo().Width / tileWidth;
	int h = texture->GetInfo().Height / tileHeight;
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			RECT r;
			r.left = j * tileWidth;
			r.top = i * tileHeight;
			r.right = r.left + tileWidth;
			r.bottom = r.top + tileHeight;

			tiles.push_back(r);
		}
	}
}

void Tileset::Draw(int id, float x, float y, int alpha, bool flip)
{
	if (id >= 0)
	{
		Graphics::GetInstance()->Draw(x, y, texture, tiles[id], alpha, flip);
	}
}


Tilesets* Tilesets::_instance = 0;

Tilesets* Tilesets::GetInstance()
{
	if (!_instance) _instance = new Tilesets;
	return _instance;
}

void Tilesets::Add(int id, int texture_id, int w, int h)
{
	LPTILESET tileset = new Tileset(Textures::GetInstance()->Get(texture_id), w, h);
	tileset->LoadTiles();
	tilesets[id] = tileset;
}

void Tilesets::Remove(int id)
{
	delete tilesets[id];
	tilesets.erase(id);
}

void Tilesets::Clear()
{
	for (std::unordered_map<int, LPTILESET>::iterator itr = tilesets.begin(); itr != tilesets.end(); itr++)
	{
		if (itr->second) delete itr->second;
	}
	tilesets.clear();
}