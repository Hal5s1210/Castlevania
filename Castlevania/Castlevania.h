#pragma once
#include <Windows.h>
#include <d3d9.h>
#include "Game.h"

class GameKeyHandler : public KeyEventHandler
{
public:
	void KeyState(BYTE* state);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
};


class Castlevania
{
private:
	LPDIRECT3DDEVICE9 d3ddv;
	LPD3DXSPRITE spriteHandler;

	GameKeyHandler* keyHandler;

public:
	Castlevania();
	~Castlevania();

	void LoadResources();
	void Update(DWORD dt);
	void Render();

	LPKEYEVENTHANDLER GetKeyHandler();
};

