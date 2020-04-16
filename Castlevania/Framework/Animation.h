#pragma once

#include "Sprite.h"

class Animation
{
public:
	struct Frame
	{
		LPSPRITE Sprite;
		int Time;
		Frame(LPSPRITE s, int t) : Sprite(s), Time(t) {}
	};

private:
	DWORD lastFrameTime;
	bool paused;
	bool frameReset;

	std::vector<Frame*> frames;

public:
	Animation();
	Animation* Clone();
	void AddFrame(Frame* frame);
	void Pause(int time = 0) { paused = true; }
	void Play() { paused = false; }
	bool IsFrameReset() { return frameReset; }
	void CopyFrames(std::vector<Frame*> frames);
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
	void Clear();
	LPANIMATION Get(int id) { return animations[id]; }

};
