#include "Game.h"


Game::Game()
{
	_hwnd = 0;
	_graphics = Graphics::GetInstance();
	_input = Input::GetInstance();
	_sound = Sound::GetInstance();

	view = Viewport::GetInstance();
}


Game::~Game()
{
	delete _graphics;
	delete _input;
	delete _sound;
	delete view;
}


bool Game::Init(HINSTANCE hInstance, int nCmdShow, LPCTSTR WindowTitle, int ScreenW, int ScreenH, int FrameRate)
{
	_hwnd = CreateGameWindow(hInstance, nCmdShow, WindowTitle, ScreenW + 16, ScreenH + 39);

	if (!_hwnd)
	{
		OutputDebugString(L"[ERROR] CreateWindow failed\n");
		return false;
	}

	if (!_graphics->Init(_hwnd))
	{
		OutputDebugString(L"[ERROR] CreateGraphicsDevice failed\n");
		return false;
	}

	SetWindowPos(_hwnd, 0, 0, 0, ScreenW * 2 + 16, ScreenH * 2 + 39, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	if (!_input->Init(_hwnd))
	{
		OutputDebugString(L"[ERROR] CreateInputDevice failed\n");
		return false;
	}

	if (!_sound->Init(_hwnd))
	{
		OutputDebugString(L"[ERROR] CreateSoundDevice failed\n");
		return false;
	}

	tickPerFrame = 1000 / FrameRate;

	view->SetSize(ScreenW, ScreenH);

	OutputDebugString(L"[INFO] CreateWindow done\n");
	return true;
}


void Game::Run()
{
	frameStart = GetTickCount();
	
	OutputDebugString(L"[INFO] Begin game loop\n");

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;

			Update(dt);
			Render();
		}
		else Sleep(tickPerFrame - dt);

	}

	OutputDebugString(L"[INFO] End game loop\n");


}


HWND Game::CreateGameWindow(HINSTANCE hInstance, int nCmdShow, LPCTSTR WindowTitle, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = L"GameWindow";
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd = CreateWindow(
		wc.lpszClassName,
		WindowTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		ScreenWidth,
		ScreenHeight,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}


LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}