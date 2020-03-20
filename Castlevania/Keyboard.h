#pragma once

#include "Game.h"

#define PAD_UP			DIK_UP
#define PAD_DOWN		DIK_DOWN
#define PAD_LEFT		DIK_LEFT
#define PAD_RIGHT		DIK_RIGHT

#define BUTTON_START	DIK_Q
#define BUTTON_SELECT	DIK_W
#define BUTTON_A		DIK_A
#define BUTTON_B		DIK_S


class Keyboard : public KeyEventHandler
{
public:
	void KeyState(BYTE* state);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
};

