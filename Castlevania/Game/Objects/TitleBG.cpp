#include "TitleBG.h"


TitleBG::TitleBG()
{
	LPTEXTURE texture = Textures::GetInstance()->Get(TITLE_BG_TEX_ID);

	LPANIMATION s = new Animation(texture);
	s->AddFrame(0, 0, 256, 240);
	AddAnimation(s);

	SetAnimation(TITLE_BG_ANIMATION);
}

TitleBG::~TitleBG()
{
	animations.clear();
}

void TitleBG::Render()
{
	animations[currentAnimation]->Draw(x, y);
}
