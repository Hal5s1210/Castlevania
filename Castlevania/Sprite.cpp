#include "Sprite.h"
#include "Game.h"

Sprite::Sprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	this->id = id;
	rect.left = left;
	rect.top = top;
	rect.right = right;
	rect.bottom = bottom;
	texture = tex;
}

void Sprite::Draw(float x, float y, int alpha)
{
	Game::GetInstance()->Draw(x, y, texture, rect, alpha);
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

void Sprites::Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	LPSPRITE sprite = new Sprite(id, left, top, right, bottom, tex);
	sprites[id] = sprite;
}

void Sprites::Remove(int id)
{
	delete sprites[id];
	sprites.erase(id);
}




Animation::Animation()
{
	currentFrame = -1;
	lastFrameTime = -1;
}

void Animation::AddFrame(int spriteId, int time)
{
	LPSPRITE sprite = Sprites::GetInstance()->Get(spriteId);
	LPFRAME frame = new Frame(sprite, time);
	frames.push_back(frame);
}

void Animation::Draw(float x, float y, int alpha)
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

	frames[currentFrame]->Sprite->Draw(x, y, alpha);
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
	delete animations[id];
	animations.erase(id);
}