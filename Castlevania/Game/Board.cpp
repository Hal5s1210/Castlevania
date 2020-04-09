#include "Board.h"
#include "..\Framework\Viewport.h"

Board::Board()
{
	texture = Textures::GetInstance()->Get(-10000);
	x = y = 0;
	score = 0;
	time = 0;
	stage = 0;
	heart = 0;
	life = 0;
	playerhp = 8;
	enemyhp = 5;
	subweapon = 0;
}

void Board::Update(DWORD dt)
{
	Viewport::GetInstance()->GetPosition(x, y);
}

void Board::Render()
{
	Draw("!", x, y);

	Draw("SCORE-", x, y + 32);
	//

	Draw("TIME", x + 104, y +32);
	//

	Draw("STAGE", x + 184, y + 32);
	//

	Draw("PLAYER", x, y + 40);
	for (int i = 0; i < 16; i++)
	{
		if (i < playerhp)
			Draw("#", x + 56 + i * 4, y + 40);
		else
			Draw("~", x + 56 + i * 4, y + 40);
	}
	Draw("@-", x + 164, y + 40);

	Draw("ENEMY", x, y + 48);
	for (int i = 0; i < 16; i++)
	{
		if (i < enemyhp)
			Draw("$", x + 56 + i * 4, y + 48);
		else
			Draw("~", x + 56 + i * 4, y + 48);
	}

	Draw("P-", x + 164, y + 48);
	//
	Draw("[", x + 128, y + 40);
	//
}

RECT Board::GetCharRect(char c, float x, float y)
{
	RECT rect;
	rect.left = rect.top = rect.right = rect.bottom = 0;

	c = toupper(c);

	int i;

	if (65 <= c && c <= 90) // alphabet
	{
		i = c - 65;

		rect.left = (i % 13) * 8;
		rect.top = (i / 13) * 8;
		rect.right = rect.left + 8;
		rect.bottom = rect.top + 8;
	}
	else if (48 <= c && c <= 57) // number
	{
		i = c - 48;

		rect.left = (i % 13) * 8;
		rect.top = 16;
		rect.right = rect.left + 8;
		rect.bottom = rect.top + 8;
	}
	else if (c == '-')
	{
		rect.left = 80;
		rect.top = 16;
		rect.right = rect.left + 8;
		rect.bottom = rect.top + 8;
	}
	else if (c == '@') // heart
	{
		rect.left = 88;
		rect.top = 16;
		rect.right = rect.left + 8;
		rect.bottom = rect.top + 8;
	}
	else if (c == '#') // player hp
	{
		rect.left = 104;
		rect.top = 0;
		rect.right = rect.left + 4;
		rect.bottom = rect.top + 8;
	}
	else if (c == '$') // enemy hp
	{
		rect.left = 104;
		rect.top = 8;
		rect.right = rect.left + 4;
		rect.bottom = rect.top + 8;
	}
	else if (c == '~') // lost hp
	{
		rect.left = 104;
		rect.top = 16;
		rect.right = rect.left + 4;
		rect.bottom = rect.top + 8;
	}
	else if (c == '[') // rectangle
	{
		rect.left = 108;
		rect.top = 0;
		rect.right = rect.left + 32;
		rect.bottom = rect.top + 22;
	}
	else if (c == '!') // black bg
	{
		rect.left = 0;
		rect.top = 24;
		rect.right = rect.left + 256;
		rect.bottom = rect.top + 64;
	}

	return rect;
}

void Board::DrawByChar(char c, float x, float y, int alpha)
{
	RECT rect;

	rect = GetCharRect(c, x, y);

	Graphics::GetInstance()->Draw(x, y, texture, rect, alpha);
}


void Board::Draw(std::string text, float x, float y, int alpha)
{
	int fixX = 0;
	for (int i = 0; i < text.size(); i++)
	{
		DrawByChar(text[i], x + i * 8, y, alpha);
	}
}
