#pragma once
#include "Game.h"
#include "Keyboard.h"
#include "GameObject.h"
#include "Scene.h"


class Castlevania : public Game
{
private:
	LPDIRECT3DDEVICE9 d3ddv;
	LPD3DXSPRITE spriteHandler;

	Scenes* scenes;

	void Update(DWORD dt);
	void Render();

public:
	Castlevania();
	~Castlevania();

	void LoadResources();
};

