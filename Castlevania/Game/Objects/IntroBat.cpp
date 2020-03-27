#include "IntroBat.h"


IntroBat::IntroBat()
{
	LPTEXTURE texture = Textures::GetInstance()->Get(INTRO_BAT_TEX_ID);

	LPANIMATION s = new Animation(texture);
	s->AddFrame(0, 0, 8, 8);
	s->AddFrame(8, 0, 8, 8);
	AddAnimation(s);

	SetAnimation(INTRO_BAT_ANIMATION);
}

IntroBat::~IntroBat()
{
	animations.clear();
}

void IntroBat::Update(DWORD dt)
{
	GameObject::Update(dt);

	x += dx;
	y += dy;
}

void IntroBat::Render()
{
	animations[currentAnimation]->Draw(x, y);
}