#include "Animation.h"


Animation::Animation()
{
	paused = false;
	frameReset = false;
	lastFrameTime = -1;
}

void Animation::AddFrame(int spriteid, int time)
{
	LPSPRITE s = Sprites::GetInstance()->Get(spriteid);
	Frame* f = new Frame(s, time);
	frames.push_back(f);
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