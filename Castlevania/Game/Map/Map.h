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
	int** mapMatrix;
	std::vector<RECT> tiles;
	std::vector<int> collisionTiles;

	void LoadTiles();
	void LoadCollisionTiles(pugi::xml_node node);
	void LoadMatrix(pugi::xml_node node);
	std::vector<int> split(const std::string& s, char delimiter);

public:
	~Map();

	void LoadMap(pugi::xml_node node);
	void GetMapObject(std::vector<LPGAMEOBJECT>* objlist);
	void Render(float x = 0, float y = 0);
};



class Platform :public GameObject
{
	int bbw, bbh;
public:
	Platform()
	{
		LPTEXTURE texture = Textures::GetInstance()->Get(-100);

		LPANIMATION s1 = new Animation(texture);
		s1->AddFrame(0, 0, 16, 16);
		AddAnimation("ani", s1);

		SetAnimation("ani");
	}

	void Render(float x, float y)
	{
		currentAnimation->Draw(this->x + x, this->y + y);
	}
	void SetBoundSize(int w, int h) { bbw = w; bbh = h; }
	void GetBoundingBox(float& l, float& t, float& r, float& b)
	{
		l = x;
		t = y;
		r = l + bbw;
		b = r + bbh;
	}
};

