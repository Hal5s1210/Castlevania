#pragma once
#include <unordered_map>
#include <d3dx9.h>


class Texture
{
private:
	LPDIRECT3DTEXTURE9 texture;
	D3DXIMAGE_INFO info;
public:
	Texture(LPDIRECT3DTEXTURE9 texture, D3DXIMAGE_INFO info) :texture(texture), info(info) {}
	~Texture() { texture->Release(); }
	LPDIRECT3DTEXTURE9 GetTexture() { return texture; }
	D3DXIMAGE_INFO GetInfo() { return info; }
};
typedef Texture* LPTEXTURE;



class Textures
{
private:
	static Textures* _instance;

	std::unordered_map<int, LPTEXTURE> textures;

public:
	Textures();

	static Textures* GetInstance();

	void Add(int id, LPCWSTR filePath, D3DCOLOR transparentColor);
	void Remove(int id);
	void Clear();
	LPTEXTURE Get(int id) { return textures[id]; }

};