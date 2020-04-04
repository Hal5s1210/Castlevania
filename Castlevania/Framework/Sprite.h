#pragma once

#include "Texture.h"
#include <unordered_map>
#include <vector>

class Sprite
{
private:
	int id;
	LPTEXTURE texture;
	RECT rect;
public:
	Sprite(int id, int textureid, int l, int t, int r, int b);

	RECT GetRect() { return rect; }
	void Draw(float x, float y, int alpha = 255, bool flip = false);
};
typedef Sprite* LPSPRITE;


class Sprites
{
private:
	static Sprites* _instance;

	std::unordered_map<int, LPSPRITE> sprites;

public:
	Sprites();

	static Sprites* GetInstance();

	void Add(int id, LPSPRITE sprite);
	void Remove(int id);
	LPSPRITE Get(int id) { return sprites[id]; }

};



