#include "TitleText.h"

TitleText::TitleText()
{
	LPTEXTURE texture = Textures::GetInstance()->Get(TEXTURE_TITLETEXT_ID);

	LPANIMATION s1 = new Animation(texture);
	s1->AddFrame(0, 0, 112, 8);
	AddAnimation("ani1", s1);

	LPANIMATION s2 = new Animation(texture);
	s2->AddFrame(0, 0, 112, 8);
	s2->AddFrame(0, 8, 112, 8);
	AddAnimation("ani2", s2);

	SetAnimation("ani1");
}

void TitleText::Render(float x, float y)
{
	currentAnimation->Draw(this->x + x, this->y + y);
}
