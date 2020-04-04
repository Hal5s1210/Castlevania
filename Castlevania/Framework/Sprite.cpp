#include "Sprite.h"
#include "Game.h"

Sprite::Sprite(int id, int textureid, int l, int t, int w, int h)
{
	this->id = id;
	texture = Textures::GetInstance()->Get(textureid);
	rect.left = l;
	rect.top = t;
	rect.right = l + w;
	rect.bottom = t + h;
}

void Sprite::Draw(float x, float y, int alpha, bool flip)
{
	Graphics::GetInstance()->Draw(x, y, texture, rect, alpha, flip);
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

void Sprites::Add(int id, LPSPRITE animation)
{
	if (sprites[id] != NULL) return;
	sprites[id] = animation;
}

void Sprites::Remove(int id)
{
	if (!sprites[id]) delete sprites[id];
	sprites.erase(id);
}