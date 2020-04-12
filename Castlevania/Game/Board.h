#pragma once

#include "..\Framework\Texture.h"
#include "..\Framework\Graphics.h"

class Board
{
private:
	LPTEXTURE texture;
	float x, y;

	int score;
	int time;
	int stage;
	int heart;
	int life;
	int playerhp;
	int enemyhp;
	int shot;
	int subweapon;


	RECT GetCharRect(char c, float x, float y);
	void DrawByChar(char c, float x, float y, int alpha = 255);
	void Draw(std::string text, float x, float y, int alpha = 255);

public:
	Board();

	void Update(DWORD dt);
	void Render();
};

	
