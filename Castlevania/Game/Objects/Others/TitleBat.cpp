#include "TitleBat.h"

TitleBat::TitleBat()
{
	LPTEXTURE texture = Textures::GetInstance()->Get(TEXTURE_TITLEBAT_ID);

	LPANIMATION s1 = new Animation(texture);
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			s1->AddFrame(x * 72, y * 56, 72, 56, 50);
		}
	}
	AddAnimation("ani1", s1);

	LPANIMATION s2 = new Animation(texture);
	s2->AddFrame(576, 168, 72, 56, 50);
	s2->AddFrame(504, 168, 72, 56, 50);
	s2->AddFrame(576, 168, 72, 56, 50);
	s2->AddFrame(648, 168, 72, 56, 50);
	AddAnimation("ani2", s2);

	SetAnimation("ani1");
}

void TitleBat::Update(DWORD dt)
{
	if (currentAnimation->CurrentFrameIndex() == 39)
	{
		SetAnimation("ani2");
	}
}

void TitleBat::Render(float x, float y)
{
	currentAnimation->Draw(this->x + x, this->y + y);
}

