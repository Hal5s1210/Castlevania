#include "Board.h"
#include "..\Framework\Viewport.h"
#include <sstream>
#include <iomanip>

Board::Board()
{
	texture = Textures::GetInstance()->Get(-10000);
	x = 0;
	y = 0;
	score = 0;
	time = 300;
	stage = 1;
	heart = 0;
	life = 2;
	playerhp = 16;
	enemyhp = 16;
	shot = 0;
	subweapon = 0;
}

void Board::Update(DWORD dt)
{
	Viewport::GetInstance()->GetPosition(x, y);
}

void Board::Render()
{
	std::stringstream ss;
	//draw black
	Draw("?", x, y);

	//draw score
	Draw("SCORE-", x, y + 16);
	ss << std::setw(6) << std::setfill('0') << score;
	Draw(ss.str(), x + 48, y + 16);
	ss.str("");

	//draw time
	Draw("TIME", x + 104, y +16);
	ss << std::setw(4) << std::setfill('0') << time;
	Draw(ss.str(), x + 144, y + 16);
	ss.str("");

	//draw stage
	Draw("STAGE", x + 184, y + 16);
	ss << std::setw(2) << std::setfill('0') << stage;
	Draw(ss.str(), x + 232, y + 16);
	ss.str("");

	//draw player hp
	Draw("PLAYER", x, y + 24);
	for (int i = 0; i < 16; i++)
	{
		if (i < playerhp)
			Draw("!", x + 56 + i * 4, y + 24);
		else
			Draw("#", x + 56 + i * 4, y + 24);
	}
	 
	//draw heart
	Draw("~-", x + 172, y + 24);
	ss << std::setw(2) << std::setfill('0') << heart;
	Draw(ss.str(), x + 188, y + 24);
	ss.str("");

	//draw enemy hp
	Draw("ENEMY", x, y + 32);
	for (int i = 0; i < 16; i++)
	{
		if (i < enemyhp)
			Draw("@", x + 56 + i * 4, y + 32);
		else
			Draw("#", x + 56 + i * 4, y + 32);
	}

	//draw life
	Draw("P-", x + 172, y + 32);
	ss << std::setw(2) << std::setfill('0') << life;
	Draw(ss.str(), x + 188, y + 32);
	ss.str("");

	// draw rectangle
	Draw("[", x + 128, y + 24);

	//draw subwepon
	switch (subweapon)
	{
	case 1:
		Draw("$", x + 136, y + 27);
		break;
	case 2:
		Draw("%", x + 136, y + 27);
		break;
	case 3:
		Draw("^", x + 136, y + 27);
		break;
	case 4:
		Draw("&", x + 136, y + 27);
		break;
	case 5:
		Draw("*", x + 136, y + 27);
		break;
	default:
		break;
	}

	//draw shot
	if(shot == 1)
		Draw("(", x + 212, y + 24);
	else if(shot ==2)
		Draw(")", x + 212, y + 24);

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
	else if (c == '~') // heart
	{
		rect.left = 88;
		rect.top = 16;
		rect.right = rect.left + 8;
		rect.bottom = rect.top + 8;
	}
	else if (c == '!') // player hp
	{
		rect.left = 0;
		rect.top = 46;
		rect.right = rect.left + 4;
		rect.bottom = rect.top + 8;
	}
	else if (c == '@') // enemy hp
	{
		rect.left = 4;
		rect.top = 46;
		rect.right = rect.left + 4;
		rect.bottom = rect.top + 8;
	}
	else if (c == '#') // lost hp
	{
		rect.left = 8;
		rect.top = 46;
		rect.right = rect.left + 4;
		rect.bottom = rect.top + 8;
	}
	else if (c == '[') // rectangle
	{
		rect.left = 0;
		rect.top = 24;
		rect.right = rect.left + 32;
		rect.bottom = rect.top + 22;
	}
	else if (c == '$') // sub danger
	{
		rect.left = 32;
		rect.top = 24;
		rect.right = rect.left + 16;
		rect.bottom = rect.top + 16;
	}
	else if (c == '%') // sub axe
	{
		rect.left = 48;
		rect.top = 24;
		rect.right = rect.left + 16;
		rect.bottom = rect.top + 16;
	}
	else if (c == '^') // sub boomrang
	{
		rect.left = 64;
		rect.top = 24;
		rect.right = rect.left + 16;
		rect.bottom = rect.top + 16;
	}
	else if (c == '&') // sub holy
	{
		rect.left = 32;
		rect.top = 40;
		rect.right = rect.left + 16;
		rect.bottom = rect.top + 16;
	}
	else if (c == '*') // sub stopwatch
	{
		rect.left = 48;
		rect.top = 40;
		rect.right = rect.left + 16;
		rect.bottom = rect.top + 16;
	}
	else if (c == '(') // double shot
	{
		rect.left = 64;
		rect.top = 40;
		rect.right = rect.left + 16;
		rect.bottom = rect.top + 16;
	}
	else if (c == ')') // triple shot
	{
		rect.left = 80;
		rect.top = 40;
		rect.right = rect.left + 16;
		rect.bottom = rect.top + 16;
	}
	else if (c == '?') // black
	{
		rect.left = 64;
		rect.top = 54;
		rect.right = rect.left + 257;
		rect.bottom = rect.top + 48;
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
