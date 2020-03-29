#include "TitleBG.h"


TitleBG::TitleBG()
{
	LPTEXTURE texture = Textures::GetInstance()->Get(TEXTURE_TITLEBG_ID);

	LPANIMATION s = new Animation(texture);
	s->AddFrame(0, 0, 256, 240);
	AddAnimation("ani", s);

	SetAnimation("ani");
}

void TitleBG::Render(float x, float y)
{
	currentAnimation->Draw(this->x + x, this->y + y);
}
