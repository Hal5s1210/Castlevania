#pragma once

#define WINDOW_CLASS_NAME L"GameWindow"
#define MAIN_WINDOW_TITLE L"Castlevania"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(255, 255, 200)
#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 240

#define MAX_FRAME_RATE 60


#include <Windows.h>
#include "Debug.h"
#include "Graphics.h"
#include "Input.h"
#include "Sound.h"
#include "Viewport.h"


class Game
{
private:
	HWND _hwnd;
	Graphics* _graphics;
	Input* _input;
	Sound* _sound;
	Viewport* view;

	MSG msg;
	int done;
	DWORD frameStart;
	DWORD tickPerFrame;

	HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, LPCTSTR WindowTitle, int ScreenWidth, int ScreenHeight);

protected:
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;

public:
	Game();
	~Game();

	bool Init(HINSTANCE hInstance, int nCmdShow, LPCTSTR WindowTitle, int screenW, int screenH , int FrameRate);
	virtual void LoadResources() = 0;
	void Run();

};

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
