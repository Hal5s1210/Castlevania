#include "Sprite.h"
#include "Game.h"


Animation::Animation(LPTEXTURE tex)
{
	texture = tex;
	paused = false;
	currentFrame = -1;
	lastFrameTime = -1;
}

void Animation::AddFrame(int left, int top, int width, int height, int time)
{
	RECT rect;
	rect.left = left;
	rect.top = top;
	rect.right = left + width;
	rect.bottom = top + height;
	LPSRPITE frame = new Sprite(rect, time);
	frames.push_back(frame);
}

void Animation::Draw(float x, float y, int alpha, bool flip)
{
	DWORD now = GetTickCount();
	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames[currentFrame]->Time;
		if (now - lastFrameTime > t)
		{
			lastFrameTime = now;

			if (!paused)
				currentFrame++;

			if (currentFrame >= frames.size()) currentFrame = 0;
		}
	}

	Graphics::GetInstance()->Draw(x, y, texture, frames[currentFrame]->Rect, alpha, flip);
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
	animations[id] = animation;
}

void Animations::Remove(int id)
{
	if (!animations[id]) delete animations[id];
	animations.erase(id);
}