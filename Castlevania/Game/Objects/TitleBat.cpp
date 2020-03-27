#include "TitleBat.h"

TitleBat::TitleBat()
{
	LPTEXTURE texture = Textures::GetInstance()->Get(TITLE_BAT_TEX_ID);

	LPANIMATION s1 = new Animation(texture);
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			s1->AddFrame(x * 72, y * 56, 72, 56, 50);
		}
	}
	AddAnimation(s1);

	LPANIMATION s2 = new Animation(texture);
	s2->AddFrame(576, 168, 72, 56, 50);
	s2->AddFrame(504, 168, 72, 56, 50);
	s2->AddFrame(576, 168, 72, 56, 50);
	s2->AddFrame(648, 168, 72, 56, 50);
	AddAnimation(s2);

	SetAnimation(TITLE_BAT_ANIMATION_1);
}

void TitleBat::Update(DWORD dt)
{
	if (animations[currentAnimation]->CurrentFrameIndex() == 39)
	{
		SetAnimation(TITLE_BAT_ANIMATION_2);
	}
}

void TitleBat::Render()
{
	animations[currentAnimation]->Draw(x, y);

}

TitleBat::~TitleBat()
{
	animations.clear();
}

