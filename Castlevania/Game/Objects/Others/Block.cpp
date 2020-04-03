#include "Block.h"

Block::Block()
{
	LPTEXTURE texture = Textures::GetInstance()->Get(-100);

	LPANIMATION s1 = new Animation(texture);
	s1->AddFrame(0, 0, 16, 16);
	AddAnimation(s1);

	SetAnimation(0);
}

void Block::Render(float x, float y)
{
	currentAnimation->Draw(this->x + x, this->y + y);
}
void Block::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + 16;
	b = r + 16;
}