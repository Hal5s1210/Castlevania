#pragma once

#include <dinput.h>

#define PAD_UP			DIK_UP
#define PAD_DOWN		DIK_DOWN
#define PAD_LEFT		DIK_LEFT
#define PAD_RIGHT		DIK_RIGHT

#define BUTTON_START	DIK_A
#define BUTTON_SELECT	DIK_S
#define BUTTON_A		DIK_Z
#define BUTTON_B		DIK_X

#define KEYBOARD_BUFFER_SIZE 1024

class Scene;

class IKeyEventHandler
{
public:
	virtual void KeyState(BYTE* state) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;
};
typedef IKeyEventHandler* LPKEYEVENTHANDLER;



class Input
{
private:
	static Input* _instance;

	LPDIRECTINPUT8 di;
	LPDIRECTINPUTDEVICE8 didv;

	BYTE  keyStates[256];
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];

	LPKEYEVENTHANDLER keyHandler;

public:
	Input();
	~Input();

	static Input* GetInstance();

	bool Init(HWND hwnd);
	void GetKeyHandler(LPKEYEVENTHANDLER keyHandler) { this->keyHandler = keyHandler; }
	void ProcessKeyboard();
	bool IsKeyDown(int KeyCode);

};