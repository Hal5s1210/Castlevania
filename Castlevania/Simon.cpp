#include "Simon.h"

Simon::Simon()
{
	LPTEXTURE texture = Textures::GetInstance()->Get(SIMON_TEX_ID);

	LPANIMATION s0 = new Animation(texture);
	s0->AddFrame(0, 0, 16, 32);
	AddAnimation(s0);

	LPANIMATION s1 = new Animation(texture);
	s1->AddFrame(0, 0, 16, 32);
	s1->AddFrame(0, 32, 16, 32);
	s1->AddFrame(16, 32, 16, 32);
	s1->AddFrame(0, 32, 16, 32);
	AddAnimation(s1);

	SetState(SIMON_STATE_IDLE);
}

Simon::~Simon()
{
	//Animations* sprites = Animations::GetInstance();
	animations.clear();
}

void Simon::Update(DWORD dt, std::vector<LPGAMEOBJECT>* objects)
{
	GameObject::Update(dt);

	std::vector<LPCOEVENT> coEvents;

	CalcPotentialCollisions(objects, coEvents);

	if (coEvents.empty())
	{
		x += dx;
		y += dy;
	}
	else
	{
		std::vector<LPCOEVENT> coEventResults;
		float min_tx, min_ty, nx, ny;

		FilterCollision(coEvents, coEventResults, min_tx, min_ty, nx, ny);

		x += dx * min_tx + nx * 0.4;
		y += dy * min_ty + ny * 0.4;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

	}
}

void Simon::Render()
{
	animations[currentAnimation]->Draw(x, y, 255, flip);
}

void Simon::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + 16;
	b = t + 32;
}

void Simon::SetState(int state)
{
	switch (state)
	{
	case SIMON_STATE_WALK_LEFT:
		currentAnimation = SIMON_WALK_ANIMATION;
		vx = -0.03;
		flip = false;
		break;

	case SIMON_STATE_WALK_RIGHT:
		currentAnimation = SIMON_WALK_ANIMATION;
		vx = 0.03;
		flip = true;
		break;

	case SIMON_STATE_IDLE:
		currentAnimation = SIMON_IDLE_ANIMATION;
		vx = 0;
		break;

	default:
		break;

	}
	this->state = state;
}