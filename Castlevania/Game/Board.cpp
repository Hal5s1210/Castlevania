#include "Board.h"
#include <sstream>
#include <iomanip>
#include "..\Framework\Viewport.h"
#include "ID.h"
#include "Objects\Weapons\Stopwatch.h"
#include "Scenes\Scene.h"

Board* Board::_instance = 0;

Board::Board()
{
	x = 0;
	y = 0;
	score = 0;
	time = 300;
	stage = 1;
	heart = 0;
	life = 3;
	playerhp = 16;
	enemyhp = 16;
	shot = 1;
	whip = 1;
	subweapon = 0;

	playerdeadtime = 2000;
	playerdeadtimestart = 0;

	gameover = false;
	selectchoice = 1;
}

Board* Board::GetInstance()
{
	if (!_instance) _instance = new Board;
	return _instance;
}

void Board::LoadTexture()
{
	texture = Textures::GetInstance()->Get(TEXTURE_UI_BOARD_ID);
}

void Board::Update(DWORD dt)
{
	Stopwatch::Update(dt);
	if (Stopwatch::TimeOut())
	{
		Stopwatch::TimeResume();
	}

	if (!Stopwatch::IsTimePause()) tickcount += dt;
	if (tickcount >= 1000)
	{
		if (time > 0)
			time -= tickcount / 1000;

		tickcount = tickcount % 1000;
	}

	if (time <= 0)
	{
		time = 0;
		playerhp = 0;
	}

	if (playerdeadtimestart != 0 && GetTickCount() - playerdeadtimestart > playerdeadtime)
	{
		if (life > 1)
		{
			life--;
			Scenes::GetInstance()->GetScene()->Reset();
			playerhp = enemyhp = 16;
			playerdeadtimestart = 0;
		}
	}

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
	if (shot == 2)
		Draw("(", x + 212, y + 24);
	else if (shot == 3)
		Draw(")", x + 212, y + 24);
}

void Board::RenderGameover()
{
	if (playerdeadtimestart == 0) return;
	if (GetTickCount() - playerdeadtimestart > playerdeadtime - 500)
	{
		Draw("?", x, y + 48);
		Draw("?", x, y + 96);
		Draw("?", x, y + 144);
		Draw("?", x, y + 192);

		if (gameover)
		{
			Draw("CONTINUE", x + 96, y + 132);
			Draw("GAMEOVER", x + 96, y + 156);
			if (selectchoice == 1)
				Draw("~", x + 80, y + 132);
			else
				Draw("~", x + 80, y + 156);
		}
	}
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
		rect.right = rect.left + 256;
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

void Board::GetSimonData(Whip* whip, SubWeapon* sub)
{
	whip->SetLevel(this->whip);
	sub->SetWeapon(subweapon, shot, heart);
}

void Board::PlayerHit(int damage)
{
	playerhp -= damage;
	if (playerhp < 0) playerhp = 0;
}

void Board::PlayerDie()
{
	playerdeadtimestart = GetTickCount();
	if (life == 1)
		gameover = true;
}

void Board::BossHit(int damage)
{
	enemyhp -= damage;
	if (enemyhp < 0) enemyhp = 0;
}


void Board::ItemClaimed(LPITEM item)
{
	item->Claim();
	int  effect_id = 0;
	switch (item->GetType())
	{
	case Item::Whip:
		whip++;
		if (whip > 3) whip = 3;
		Scenes::GetInstance()->GetScene()->GetPlayer()->UpgradeWhip();
		break;

	case Item::Dagger:subweapon = 1; break;
	case Item::Axe:	subweapon = 2; break;
	case Item::Boomerang: subweapon = 3; break;
	case Item::HolyWater: subweapon = 4; break;
	case Item::StopWatch: subweapon = 5; break;

	case Item::SmallHeart: heart += 1; break;
	case Item::BigHeart: heart += 5; break;
		
	case Item::LifeUp: life += 1; break;

	case Item::Pork: playerhp = 16; break;
		
	case Item::DoubleShot: shot = 2; break;
	case Item::TripleShot: shot = 3; break;

	case Item::Money100: score += 100; effect_id = EFFECT_100POINT_ID; break;
	case Item::Money400: score += 400; effect_id = EFFECT_400POINT_ID; break;
	case Item::Money700: score += 700; effect_id = EFFECT_700POINT_ID; break;
	case Item::Money1000: score += 1000; effect_id = EFFECT_1000POINT_ID; break;
	case Item::Crown: score += 2000; effect_id = EFFECT_2000POINT_ID; break;
	case Item::Chest: score += 4000; effect_id = EFFECT_4000POINT_ID; break;

	case Item::Cross:
		Scenes::GetInstance()->GetScene()->KillAllEnemies();
		Effect::Flash();
		break;

	case Item::Crystall: break;

	case Item::Invisible: Scenes::GetInstance()->GetScene()->GetPlayer()->GoInvisible(); break;

	default:
		break;
	}
	item->RunEffect(effect_id);
}


void Board::ConfirmSelection()
{
	playerdeadtimestart = 0;
	gameover = false;
	if (selectchoice == 1)
	{
		Scenes::GetInstance()->GetScene()->Reset();
		Reset();
	}
	else
	{
		Scenes::GetInstance()->NextScene(-1);
		Reset();
	}
}

void Board::ChangeSelection()
{
	if (selectchoice == 1) selectchoice = 2;
	else if (selectchoice == 2)selectchoice = 1;
}


void Board::Reset()
{
	x = 0;
	y = 0;
	score = 0;
	time = 300;
	heart = 0;
	life = 3;
	playerhp = 16;
	enemyhp = 16;
	shot = 1;
	whip = 1;
	subweapon = 0;
	Viewport::GetInstance()->SetAuto(false);
}