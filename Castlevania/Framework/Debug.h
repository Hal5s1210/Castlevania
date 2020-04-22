#pragma once

#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>

class Debug
{
private:
	static bool _enable;

public:
	static bool IsEnable() { return _enable; }
	static void EnableDebugging() { _enable = !_enable; }
	static void DebugOut(const wchar_t* fmt, ...);
	static void RenderBoundBox(float x, float y, int l, int t, int r, int b);
};
