#include "Graphics.h"
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
	LPDIRECT3D9 d3d = Direct3DCreate9(D3D_SDK_VERSION);

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

	if (flip)
	{
		D3DXMATRIX a, b;
		spriteHandler->GetTransform(&a);
		D3DXMatrixTransformation2D(&b, &D3DXVECTOR2(int(x), int(y)), 0.f, &D3DXVECTOR2(-1.f, 1.f), NULL, 0.f, NULL);

		D3DXVECTOR3 p(floor(x - (rect.right - rect.left)), floor(y), 0);

		spriteHandler->SetTransform(&(a * b));
		spriteHandler->Draw(texture->GetTexture(), &rect, NULL, &p, D3DCOLOR_ARGB(alpha, 255, 255, 255));
		spriteHandler->SetTransform(&a);
	}
	else
	{
		D3DXVECTOR3 p(floor(x), floor(y), 0);

		spriteHandler->Draw(texture->GetTexture(), &rect, NULL, &p, D3DCOLOR_ARGB(alpha, 255, 255, 255));
	}
}

void Graphics::FillColor(int r, int g, int b)
{
	d3ddv->ColorFill(backBuffer, NULL, D3DCOLOR_XRGB(r, g, b));
}


void Graphics::SweptAABB(
	float ml, float mt, float mr, float mb,
	float dx, float dy,
	float sl, float st, float sr, float sb,
	float& t, float& nx, float& ny)
{
	float dx_entry, dx_exit, tx_entry, tx_exit;
	float dy_entry, dy_exit, ty_entry, ty_exit;

	float t_entry;
	float t_exit;

	t = -1.0f;			// no collision
	nx = ny = 0;

	//
	// Broad-phase test 
	//

	float bl = dx > 0 ? ml : ml + dx;
	float bt = dy > 0 ? mt : mt + dy;
	float br = dx > 0 ? mr + dx : mr;
	float bb = dy > 0 ? mb + dy : mb;

	if (br < sl || bl > sr || bb < st || bt > sb) return;


	if (dx == 0 && dy == 0) return;		// moving object is not moving > obvious no collision

	if (dx > 0)
	{
		dx_entry = sl - mr;
		dx_exit = sr - ml;
	}
	else if (dx < 0)
	{
		dx_entry = sr - ml;
		dx_exit = sl - mr;
	}


	if (dy > 0)
	{
		dy_entry = st - mb;
		dy_exit = sb - mt;
	}
	else if (dy < 0)
	{
		dy_entry = sb - mt;
		dy_exit = st - mb;
	}

	if (dx == 0)
	{
		tx_entry = -99999999999;
		tx_exit = 99999999999;
	}
	else
	{
		tx_entry = dx_entry / dx;
		tx_exit = dx_exit / dx;
	}

	if (dy == 0)
	{
		ty_entry = -99999999999;
		ty_exit = 99999999999;
	}
	else
	{
		ty_entry = dy_entry / dy;
		ty_exit = dy_exit / dy;
	}


	if ((tx_entry < 0.0f && ty_entry < 0.0f) || tx_entry > 1.0f || ty_entry > 1.0f) return;

	t_entry = max(tx_entry, ty_entry);
	t_exit = min(tx_exit, ty_exit);

	if (t_entry > t_exit) return;

	t = t_entry;

	if (tx_entry > ty_entry)
	{
		ny = 0.0f;
		dx > 0 ? nx = -1.0f : nx = 1.0f;
	}
	else
	{
		nx = 0.0f;
		dy > 0 ? ny = -1.0f : ny = 1.0f;
	}
}