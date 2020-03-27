#include "IntroBG.h"

IntroBG::IntroBG()
{
	LPTEXTURE texture = Textures::GetInstance()->Get(INTRO_BG_TEX_ID);

	LPANIMATION s = new Animation(texture);
	s->AddFrame(0, 0, 256, 192);
	AddAnimation(s);

	SetState(INTRO_BG_ANIMATION);
}

IntroBG::~IntroBG()
{
	animations.clear();
}

void IntroBG::Render()
{
	animations[currentAnimation]->Draw(x, y);
}