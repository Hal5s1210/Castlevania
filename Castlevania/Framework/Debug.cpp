#include <Windows.h>
#include "Debug.h"
#include "Graphics.h"
#include "Viewport.h"

void NSDebug::DebugOut(const wchar_t* fmt, ...)
{
	va_list argp;
	va_start(argp, fmt);
	wchar_t dbg_out[4096];
	vswprintf_s(dbg_out, fmt, argp);
	va_end(argp);
	OutputDebugString(dbg_out);
}	

void NSDebug::RenderBoundBox(float x, float y, int l, int t, int r, int b)
{
	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = r - l;
	rect.bottom = b - t;

	float cam_x, cam_y;
	Viewport::GetInstance()->GetPosition(cam_x, cam_y);

	float xx, yy;
	xx = l - cam_x + x;
	yy = t - cam_y + y;
	
	LPTEXTURE tex = Textures::GetInstance()->Get(-69);
	LPD3DXSPRITE sp = Graphics::GetInstance()->GetSpriteHandler();

	sp->Draw(tex->GetTexture(), &rect, NULL, &D3DXVECTOR3(int(xx), int(yy), 0), D3DCOLOR_ARGB(128, 255, 255, 255));
}