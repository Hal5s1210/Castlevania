#include "Sprite.h"
#include "Game.h"


Sprite::Sprite(LPDIRECT3DTEXTURE9 tex)
{
	texture = tex;
	currentFrame = -1;
	lastFrameTime = -1;
}

void Sprite::AddFrame(int left, int top, int width, int height, int time)
{
	RECT rect;
	rect.left = left;
	rect.top = top;
	rect.right = left + width;
	rect.bottom = top + height;
	LPFRAME frame = new Frame(rect, time);
	frames.push_back(frame);
}

void Sprite::Draw(float x, float y, int alpha)
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

			if (currentFrame == frames.size()) currentFrame = 0;
		}
	}

	Game::GetInstance()->Draw(x, y, texture, frames[currentFrame]->Rect, alpha);
}




Sprites* Sprites::_instance = 0;

Sprites::Sprites()
{
}

Sprites* Sprites::GetInstance()
{
	if (!_instance) _instance = new Sprites;
	return _instance;
}

void Sprites::Add(int id, LPSPRITE sprite)
{
	sprites[id] = sprite;
}

void Sprites::Remove(int id)
{
	if (!sprites[id]) delete sprites[id];
	sprites.erase(id);
}