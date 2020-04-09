#pragma once

#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>

namespace NSDebug
{
	void DebugOut(const wchar_t* fmt, ...);
	void RenderBoundBox(float x, float y, int l, int t, int r, int b);
}
