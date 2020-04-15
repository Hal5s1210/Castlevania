#include "Animation.h"


Animation::Animation()
{
	paused = false;
	frameReset = false;
	lastFrameTime = -1;
}
void Animation::CopyFrames(std::vector<Frame*> frames)
{
	for (Frame* f : this->frames)
		frames.push_back(f);
}


Animation* Animation::Clone()
{
	Animation* ani = new Animation;
	for (Frame* f : frames)
	{
		ani->AddFrame(f);
	}
	return ani;
}

void Animation::AddFrame(Frame* frame)
{
	frames.push_back(frame);
}

void Animation::Draw(int& frame, float x, float y, int alpha, bool flip)
{
	DWORD now = GetTickCount();
	int i = frame;

	if (frame == -1)
	{
		frame = i = 0;
		frameReset = false;
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames[frame]->Time;
		if (now - lastFrameTime > t)
		{
			lastFrameTime = now;
			frameReset = false;

			if (!paused) frame++;

			if (frame >= frames.size())
			{
				frame = 0;
				frameReset = true;
			}
		}
	}

	frames[i]->Sprite->Draw(x, y, alpha, flip);
}


Animations* Animations::_instance = 0;

Animations::Animations()
{
}

Animations* Animations::GetInstance()
{
	if (!_instance) _instance = new Animations;
	return _instance;
}

void Animations::Add(int id, LPANIMATION animation)
{
	if (animations[id] != NULL) return;
	animations[id] = animation;
}

void Animations::Remove(int id)
{
	if (!animations[id]) delete animations[id];
	animations.erase(id);
}

void Animations::Clear()
{
	for (std::unordered_map<int, LPANIMATION>::iterator itr = animations.begin(); itr != animations.end(); itr++)
	{
		if (itr->second) delete itr->second;
	}
	animations.clear();
}