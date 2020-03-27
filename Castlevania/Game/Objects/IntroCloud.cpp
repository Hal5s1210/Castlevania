#include "IntroCloud.h"


IntroCloud::IntroCloud()
{
	LPTEXTURE texture = Textures::GetInstance()->Get(INTRO_CLOUD_TEX_ID);

	LPANIMATION s = new Animation(texture);
	s->AddFrame(0, 0, 32, 16);
	AddAnimation(s);

	SetAnimation(INTRO_CLOUD_ANIMATION);
}

IntroCloud::~IntroCloud()
{
	animations.clear();
}

void IntroCloud::Update(DWORD dt)
{
	GameObject::Update(dt);

	x += dx;
	y += dy;
}

void IntroCloud::Render()
{
	animations[currentAnimation]->Draw(x, y);
}