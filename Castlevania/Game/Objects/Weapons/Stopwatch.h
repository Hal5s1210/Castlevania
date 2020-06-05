#pragma once

#include <d3d9.h>

class Stopwatch
{
private:
	static bool pause;
	static bool timeout;
	static DWORD stoptimestart;
	static DWORD timestop;

public:
	static void TimeStop(int level = 0);
	static void TimeResume();
	static bool IsTimePause() { return pause; }
	static bool TimeOut() { return timeout; }
	static void Update(DWORD dt);
};