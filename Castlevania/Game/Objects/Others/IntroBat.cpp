#include "IntroBat.h"


IntroBat::IntroBat()
{
	LPTEXTURE texture = Textures::GetInstance()->Get(TEXTURE_INTROBAT_ID);

	LPANIMATION s = new Animation(texture);
	s->AddFrame(0, 0, 8, 8);
	s->AddFrame(8, 0, 8, 8);
	AddAnimation("ani", s);

	SetAnimation("ani");
}


void IntroBat::Update(DWORD dt)
{
	GameObject::Update(dt);

	x += dx;
	y += dy;
}

void IntroBat::Render(float x, float y)
{
	currentAnimation->Draw(this->x + x, this->y + y);
}