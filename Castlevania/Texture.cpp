#include "Texture.h"
#include "Game.h"
#include "Debug.h"

Textures* Textures::_instance = 0;

Textures::Textures()
{
}

Textures* Textures::GetInstance()
{
	if (!_instance) _instance = new Textures;
	return _instance;
}

void Textures::Add(int id, LPCWSTR filePath, D3DCOLOR transparentColor)
{
	D3DXIMAGE_INFO info;

	HRESULT hr = D3DXGetImageInfoFromFile(filePath, &info);
	if (hr != D3D_OK)
	{
		textures[id] = NULL;

		DebugOut(L"[ERROR] GetImageInfoFromFile failed: %s\n", filePath);
		return;
	}

	LPDIRECT3DDEVICE9 d3ddv = Game::GetInstance()->GetDirect3DDevice();

	LPDIRECT3DTEXTURE9 texture;

	hr = D3DXCreateTextureFromFileEx(
		d3ddv,
		filePath,
		info.Width,
		info.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		transparentColor,
		&info,
		NULL,
		&texture
	);

	if (hr != D3D_OK)
	{
		textures[id] = NULL;

		OutputDebugString(L"[ERROR] CreateTextureFromFile failed\n");
		return;
	}

	textures[id] = new Texture(texture, info);

	DebugOut(L"[INFO] Texture loaded Ok: id=%d, %s \n", id, filePath);
}

void Textures::Remove(int id)
{
	if (!textures[id]) delete textures[id];
	textures.erase(id);
}

