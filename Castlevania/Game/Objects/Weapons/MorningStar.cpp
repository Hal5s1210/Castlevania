#include "MorningStar.h"

MorningStar::MorningStar()
{
	LPTEXTURE texture = Textures::GetInstance()->Get(TEXTURE_WEAPON_ID);

	/*LPANIMATION s1 = new Animation(texture);
	s1->AddFrame(16, 0, 8, 32);
	s1->AddFrame(72, 0, 16, 24);
	s1->AddFrame(0, 48, 28, 16);
	AddAnimation("level1", s1);*/

	LPANIMATION s1 = new Animation(texture);
	s1->AddFrame(8, 0, 8, 32, 10);
	s1->AddFrame(16, 0, 8, 32, 10);
	s1->AddFrame(24, 0, 8, 32, 10);
	s1->AddFrame(32, 0, 8, 32, 10);
	AddAnimation("frame1", s1);

	LPANIMATION s2 = new Animation(texture);
	s2->AddFrame(56, 0, 16, 24, 10);
	s2->AddFrame(72, 0, 16, 24, 10);
	s2->AddFrame(88, 0, 16, 24, 10);
	s2->AddFrame(104, 0, 16, 24, 10);
	AddAnimation("frame2", s2);

	LPANIMATION s3 = new Animation(texture);
	s3->AddFrame(28, 32, 44, 16, 10);
	s3->AddFrame(72, 32, 44, 16, 10);
	s3->AddFrame(28, 48, 44, 16, 10);
	s3->AddFrame(72, 48, 44, 16, 10);
	AddAnimation("frame3", s3);
}

void MorningStar::SetFrameIndex(int i)
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

void MorningStar::Render(float x, float y, bool flip)
{
	float X = this->x;
	float Y = this->y;

	LPSRPITE frame = currentAnimation->GetFrame();
	RECT r = frame->Rect;
	int w = r.right - r.left;

	if (index <= 0)
	{
		if (!flip)X += x;
	}
	else if (index == 1)
	{
		if (!flip) X += x;
		else X -= w;
	}
	else if (index == 2)
	{
		if (!flip) X -= w;
		else X += x;
	}
	currentAnimation->Draw(X, Y, 255, flip);
}

void MorningStar::GetBoundingBox(float& l, float& t, float& r, float& b)
{
}