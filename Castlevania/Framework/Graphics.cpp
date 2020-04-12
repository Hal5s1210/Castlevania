#include "Graphics.h"
#include "Viewport.h"
#include "Debug.h"

Graphics* Graphics::_instance = 0;

Graphics::Graphics()
{
	d3d = 0;
	d3ddv = 0;
	backBuffer = 0;
	spriteHandler = 0;
}

Graphics::~Graphics()
{
	if (!spriteHandler) spriteHandler->Release();
	if (!backBuffer) backBuffer->Release();
	if (!d3ddv) d3ddv->Release();
	if (!d3d) d3d->Release();
}

Graphics* Graphics::GetInstance()
{
	if (!_instance) _instance = new Graphics;
	return _instance;
}

bool Graphics::Init(HWND hWnd)
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION);

	this->hWnd = hWnd;

	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;

	RECT r;
	GetClientRect(hWnd, &r);

	d3dpp.BackBufferHeight = r.bottom + 1;
	d3dpp.BackBufferWidth = r.right + 1;

	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddv);

	if (!d3ddv)
		return false;

	d3ddv->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);
	D3DXCreateSprite(d3ddv, &spriteHandler);

	OutputDebugString(L"[INFO] InitGraphics done;\n");
	return true;
}

void Graphics::Draw(float x, float y, LPTEXTURE texture, RECT rect, int alpha, bool flip)
{
	float cam_x, cam_y;
	Viewport::GetInstance()->GetPosition(cam_x, cam_y);

	float xx, yy;
	xx = x - cam_x;
	yy = y - cam_y;

	if (flip)
	{
		D3DXMATRIX a, b;
		spriteHandler->GetTransform(&a);
		D3DXMatrixTransformation2D(&b, &D3DXVECTOR2(xx, yy), 0.f, &D3DXVECTOR2(-1.f, 1.f), NULL, 0.f, NULL);

		D3DXVECTOR3 p(round(xx - (rect.right - rect.left)), round(yy), 0);

		spriteHandler->SetTransform(&(a * b));
		spriteHandler->Draw(texture->GetTexture(), &rect, NULL, &p, D3DCOLOR_ARGB(alpha, 255, 255, 255));
		spriteHandler->SetTransform(&a);
	}
	else
	{
		D3DXVECTOR3 p(round(xx), round(yy), 0);

		spriteHandler->Draw(texture->GetTexture(), &rect, NULL, &p, D3DCOLOR_ARGB(alpha, 255, 255, 255));
	}
}

void Graphics::FillColor(int r, int g, int b)
{
	d3ddv->ColorFill(backBuffer, NULL, D3DCOLOR_XRGB(r, g, b));
}