#pragma once

#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>

#include "Texture.h"


class Graphics
{
private:
	static Graphics* _instance;

	HWND hWnd;				

	LPDIRECT3D9 d3d;
	LPDIRECT3DDEVICE9 d3ddv;

	LPDIRECT3DSURFACE9 backBuffer;
	LPD3DXSPRITE spriteHandler;

public:
	Graphics();
	~Graphics();

	static Graphics* GetInstance();

	bool Init(HWND hWnd);

	void Draw(float x, float y, LPTEXTURE texture, RECT rect, int alpha = 255, bool flip = false);
	void FillColor(int r = 0, int g = 0, int b = 0);

	LPDIRECT3DDEVICE9 GetDirect3DDevice() { return d3ddv; }
	LPDIRECT3DSURFACE9 GetBackBuffer() { return backBuffer; }
	LPD3DXSPRITE GetSpriteHandler() { return spriteHandler; }

};

