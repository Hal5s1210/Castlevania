#pragma once

#include "Texture.h"
#include <unordered_map>
#include <vector>

class Animation
{
private:
	struct Frame
	{
		RECT Rect;
		int Time;

		Frame(RECT rect, int time) :Rect(rect), Time(time) {}

	};
	typedef Frame* LPFRAME;

	LPTEXTURE texture;

	DWORD lastFrameTime;
	int currentFrame;
	bool paused;

	std::vector<LPFRAME> frames;

public:
	Animation(LPTEXTURE tex);

	void AddFrame(int left, int top, int width, int height, int time = 100);
	void Pause() { paused = true; }
	void Play() { paused = false; }
	int GetFrame() { return currentFrame; }
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