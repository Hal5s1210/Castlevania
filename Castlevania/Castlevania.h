#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <vector>
#include "Game.h"
#include "Keyboard.h"
#include "GameObject.h"
#include "Scene.h"


class Castlevania
{
private:
	LPDIRECT3DDEVICE9 d3ddv;
	LPD3DXSPRITE spriteHandler;

	KeyEventHandler* keyHandler;

	Scenes* scenes;

public:
	Castlevania();
	~Castlevania();

	void LoadResources();
	void Update(DWORD dt);
	void Render();

	LPKEYEVENTHANDLER GetKeyHandler();
};

