#include "IntroBG.h"

IntroBG::IntroBG()
{
	LPTEXTURE texture = Textures::GetInstance()->Get(TEXTURE_INTROBG_ID);

	LPANIMATION s = new Animation(texture);
	s->AddFrame(0, 0, 256, 192);
	AddAnimation("ani", s);

	SetAnimation("ani");
}


void IntroBG::Render(float x, float y)
{
	currentAnimation->Draw(this->x + x, this->y + y);
}