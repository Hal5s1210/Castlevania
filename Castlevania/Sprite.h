#pragma once

#include "Texture.h"
#include <unordered_map>
#include <vector>

class Sprite
{
private:
	struct Frame 
	{
		RECT Rect;
		int Time;

		Frame(RECT rect, int time) :Rect(rect), Time(time) {}

	};
	typedef Frame* LPFRAME;

	LPDIRECT3DTEXTURE9 texture;

	DWORD lastFrameTime;
	int currentFrame;
	bool paused;

	std::vector<LPFRAME> frames;

public:
	Sprite(LPDIRECT3DTEXTURE9 tex);

	void AddFrame(int left, int top, int width, int height, int time = 100);
	void Reset() { currentFrame = 0; }
	void Pause() { paused = true; }
	void Play() { paused = false; }
	int GetFrame() { return currentFrame; }
	void Draw(float x, float y, int alpha = 255);

};
typedef Sprite* LPSPRITE;




class Sprites
{
private:
	static Sprites* _instance;

	std::unordered_map<int, LPSPRITE> sprites;

public:
	Sprites();

	static Sprites* GetInstance();

	void Add(int id, LPSPRITE sprite);
	void Remove(int id);
	LPSPRITE Get(int id) { return sprites[id]; }

};