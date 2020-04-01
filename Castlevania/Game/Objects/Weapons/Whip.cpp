#include "Whip.h"

Whip::Whip()
{
	LPTEXTURE texture = Textures::GetInstance()->Get(TEXTURE_WEAPON_ID);

	LPANIMATION s1 = new Animation(texture);
	s1->AddFrame(0, 0, 8, 32);
	AddAnimation("frame1", s1);

	LPANIMATION s2 = new Animation(texture);
	s2->AddFrame(40, 0, 16, 24);
	AddAnimation("frame2", s2);

	LPANIMATION s3 = new Animation(texture);
	s3->AddFrame(0, 32, 28, 16);
	AddAnimation("frame3", s3);
}

void Whip::SetFrameIndex(int i)
{
	Weapon::SetFrameIndex(i);
	switch (i)
	{
	case -1:
	case 0:
		SetAnimation("frame1");
		break;
	case 1:
		SetAnimation("frame2");
		break;
	case 2:
		SetAnimation("frame3");
		break;
	}
}

void Whip::Render(float x, float y, bool flip)
{
	float X = this->x;
	float Y = this->y;
	if (index <= 0)
	{
		if (!flip )X += x;
	}
	else if (index == 1)
	{
		if (!flip) X += x;
		else X -= 16;
	}
	else if (index == 2)
	{
		if (!flip) X -= 28;
		else X += x;
	}
	currentAnimation->Draw(X, Y, 255, flip);
}

void Whip::GetBoundingBox(float& l, float& t, float& r, float& b)
{
}
