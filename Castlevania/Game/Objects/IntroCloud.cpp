#include "IntroCloud.h"


IntroCloud::IntroCloud()
{
	LPTEXTURE texture = Textures::GetInstance()->Get(TEXTURE_INTROCLOUD_ID);

	LPANIMATION s = new Animation(texture);
	s->AddFrame(0, 0, 32, 16);
	AddAnimation("ani", s);

	SetAnimation("ani");
}

void IntroCloud::Update(DWORD dt)
{
	GameObject::Update(dt);

	x += dx;
	y += dy;
}

void IntroCloud::Render(float x, float y)
{
	currentAnimation->Draw(this->x + x, this->y + y);
}