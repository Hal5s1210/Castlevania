#pragma once

#include "Sprite.h"

class Animation
{
private:
	struct Frame
	{
		LPSPRITE Sprite;
		int Time;
		Frame(LPSPRITE s, int t) : Sprite(s), Time(t) {}
	};

	DWORD lastFrameTime;
	bool paused;
	bool frameReset;

	std::vector<Frame*> frames;

public:
	Animation();

	void AddFrame(int spriteid, int time);
	void Pause() { paused = true; }
	void Play() { paused = false; }
	bool IsFrameReset() { return frameReset; }
	LPSPRITE GetFrame(int frame) { if (frame != -1) return frames[frame]->Sprite; return frames[0]->Sprite; }
	void Draw(int& frame, float x, float y, int alpha = 255, bool flip = false);

};
typedef Animation* LPANIMATION;

typedef std::pair<LPANIMATION, int> ANIMATION;

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
