
#define MAIN_WINDOW_TITLE L"Castlevania"

#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 240

#define MAX_FRAME_RATE 60

#include "Castlevania.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Castlevania* game = new Castlevania;

	if (game->Init(hInstance, nCmdShow, MAIN_WINDOW_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT, MAX_FRAME_RATE))
	{
		game->LoadResources();
		game->Run();
	}

	delete game;

	return 0;
}