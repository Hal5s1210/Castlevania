#pragma once

#include "Texture.h"
#include <unordered_map>
#include <vector>

class Sprite
{
private:
	int id;
	RECT rect;

	LPDIRECT3DTEXTURE9 texture;

public:
	Sprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);

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

	void Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);
	void Remove(int id);
	LPSPRITE Get(int id) { return sprites[id]; }

};







class Animation
{
private:
	struct Frame 
	{
		LPSPRITE Sprite;
		int Time;

		Frame(LPSPRITE sprite, int time) :Sprite(sprite), Time(time) {}

	};
	typedef Frame* LPFRAME;

	DWORD lastFrameTime;
	int currentFrame;
	bool paused;

	std::vector<LPFRAME> frames;

public:
	Animation();

	void AddFrame(int spriteId, int time = 100);
	void Reset() { currentFrame = 0; }
	void Pause() { paused = true; }
	void Play() { paused = false; }
	int GetFrame() { return currentFrame; }
	void Draw(float x, float y, int alpha = 255);

};
typedef Animation* LPANIMATION;




class Animations
{
private:
	static Animations* _instance;

	std::unordered_map<int, LPANIMATION> animations;

public:
	Animations();

	static Animations* GetInstance();

	void Add(int id, LPANIMATION animation);
	void Remove(int id);
	LPANIMATION Get(int id) { return animations[id]; }

};