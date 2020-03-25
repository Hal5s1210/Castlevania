#pragma once

#include "Texture.h"
#include <unordered_map>
#include <vector>

struct Sprite
{
	RECT Rect;
	int Time;

	Sprite(RECT rect, int time) :Rect(rect), Time(time) {}

};
typedef Sprite* LPSRPITE;




class Animation
{
private:
	LPTEXTURE texture;

	DWORD lastFrameTime;
	int currentFrame;
	bool paused;

	std::vector<LPSRPITE> frames;

public:
	Animation(LPTEXTURE tex);

	void AddFrame(int left, int top, int width, int height, int time = 100);
	void Pause() { paused = true; }
	void Play() { paused = false; }
	void Reset() { if (frames.size() != 0) currentFrame = 0; }
	int CurrentFrameIndex() { return currentFrame; }
	LPSRPITE GetFrame() { if (currentFrame >= 0) return frames[currentFrame]; return NULL; }
	void Draw(float x, float y, int alpha = 255, bool flip = false);

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