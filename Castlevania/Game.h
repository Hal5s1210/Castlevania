#pragma once

#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>

#include "Texture.h"

#define KEYBOARD_BUFFER_SIZE 1024

class KeyEventHandler
{
public:
	virtual void KeyState(BYTE* state) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;
};

typedef KeyEventHandler* LPKEYEVENTHANDLER;

class Game
{
private:
	static Game* _instance;

	HWND hWnd;				

	LPDIRECT3D9 d3d;
	LPDIRECT3DDEVICE9 d3ddv;

	LPDIRECT3DSURFACE9 backBuffer;
	LPD3DXSPRITE spriteHandler;

	LPDIRECTINPUT8 di;
	LPDIRECTINPUTDEVICE8 didv;

	BYTE  keyStates[256];
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];

	LPKEYEVENTHANDLER keyHandler;

public:
	Game();
	~Game();

	static Game* GetInstance();

	void Init(HWND hWnd);
	void InitKeyboard(LPKEYEVENTHANDLER handler);

	void Draw(float x, float y, LPTEXTURE texture, RECT rect, int alpha = 255, bool flip = false);
	void FillColor(int r = 0, int g = 0, int b = 0);
	void ProcessKeyboard();
	bool IsKeyDown(int KeyCode);

	LPDIRECT3DDEVICE9 GetDirect3DDevice() { return d3ddv; }
	LPDIRECT3DSURFACE9 GetBackBuffer() { return backBuffer; }
	LPD3DXSPRITE GetSpriteHandler() { return spriteHandler; }

	static void SweptAABB(
		float ml, float mt, float mr, float mb,
		float dx, float dy,
		float sl, float st, float sr, float sb,
		float& t, float& nx, float& ny);

};

