#pragma once

#include "..\Framework\Texture.h"
#include "..\Framework\Graphics.h"
#include "Objects\Item.h"
#include "Objects\Weapons\Whip.h"
#include "Objects\Weapons\SubWeapon.h"

class Board
{
private:
	static Board* _instance;

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
	int whip;
	int subweapon;

	DWORD tickcount;
	bool timeout;

	DWORD playerdeadtime;
	DWORD playerdeadtimestart;

	bool gameover;

	int selectchoice;

	bool victory;
	DWORD victorytime;
	DWORD victorytimestart;

	bool done;
	DWORD donetime;
	DWORD donetimestart;

	bool pause;

	RECT GetCharRect(char c, float x, float y);
	void DrawByChar(char c, float x, float y, int alpha = 255);
	void Draw(std::string text, float x, float y, int alpha = 255);

	void Reset();

public:
	Board();

	static Board* GetInstance();

	void LoadTexture();

	void SetStage(int i) { stage = i > 0 ? i : 1; }

	void GetSimonData(Whip* whip, SubWeapon* sub);
	void PlayerHit(int damage);
	void PlayerDie();
	int GetPlayerHp() { return playerhp; }

	void BossHit(int damage);
	int GetBossHp() { return enemyhp; }
	
	bool IsPaused() { return pause; }
	void GamePause();
	void GameResume();

	void RenderGameover();

	bool IsGameOver() { return gameover; }

	bool IsDone() { return done; }

	void ConfirmSelection();
	void ChangeSelection();

	void ItemClaimed(LPITEM item);
	void AddScore(int score) { this->score += score; }
	void SubWeaponUsed(int n) { heart -= n; }
	void Update(DWORD dt);
	void Render();
};

	
