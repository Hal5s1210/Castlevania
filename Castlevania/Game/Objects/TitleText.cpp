#include "TitleText.h"

TitleText::TitleText()
{
	LPTEXTURE texture = Textures::GetInstance()->Get(TITLE_TEXT_TEX_ID);

	LPANIMATION s1 = new Animation(texture);
	s1->AddFrame(0, 0, 112, 8);
	AddAnimation(s1);

	LPANIMATION s2 = new Animation(texture);
	s2->AddFrame(0, 0, 112, 8);
	s2->AddFrame(0, 8, 112, 8);
	AddAnimation(s2);

	SetAnimation(TITLE_TEXT_ANIMATION_1);
}

void TitleText::Render()
{
	animations[currentAnimation]->Draw(x, y);
}

TitleText::~TitleText()
{
	animations.clear();
}
