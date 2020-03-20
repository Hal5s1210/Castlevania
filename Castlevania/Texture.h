#pragma once
#include <unordered_map>
#include <d3dx9.h>

class Textures
{
private:
	static Textures* _instance;

	std::unordered_map<int, LPDIRECT3DTEXTURE9> textures;

public:
	Textures();

	static Textures* GetInstance();

	void Add(int id, LPCWSTR filePath, D3DCOLOR transparentColor);
	void Remove(int id);
	LPDIRECT3DTEXTURE9 Get(int id) { return textures[id]; }

};