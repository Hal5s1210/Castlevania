#include "Weapon.h"

NoWeapon::NoWeapon()
{
	LPTEXTURE texture = Textures::GetInstance()->Get(TEXTURE_WEAPON_ID);

	LPANIMATION s3 = new Animation(texture);
	s3->AddFrame(80, 80, 8, 16);
	AddAnimation("frame3", s3);
	SetAnimation("frame3");
}

void NoWeapon::Render(float x, float y, bool flip)
{
	float X = this->x;
	float Y = this->y;
	if (index == 2)
	{
		if (!flip) X -= 8;
		else X += x;
		currentAnimation->Draw(X, Y, 255, flip);
	}
}

void NoWeapon::GetBoundingBox(float& l, float& t, float& r, float& b)
{
}

