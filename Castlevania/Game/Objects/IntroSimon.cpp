#include "IntroSimon.h"

IntroSimon::IntroSimon()
{
	LPTEXTURE texture = Textures::GetInstance()->Get(TEXTURE_SIMON_ID);

	LPANIMATION s1 = new Animation(texture);
	s1->AddFrame(0, 0, 16, 32);
	s1->AddFrame(0, 32, 16, 32);
	s1->AddFrame(16, 32, 16, 32);
	s1->AddFrame(0, 32, 16, 32);
	AddAnimation("ani1", s1);

	LPANIMATION s2 = new Animation(texture);
	s2->AddFrame(80, 0, 16, 32);
	AddAnimation("ani2", s2);

	SetAnimation("ani1");
}

void IntroSimon::Update(DWORD dt)
{
	if (x < 120)
	{
		SetAnimation("ani2");
		SetSpeed(0, 0);
		SetPosition(120, y);
	}

	GameObject::Update(dt);

	x += dx;
	y += dy;
}

void IntroSimon::Render(float x, float y)
{
	currentAnimation->Draw(this->x + x, this->y + y);
}