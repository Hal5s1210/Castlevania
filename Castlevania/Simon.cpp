#include "Simon.h"
#include "Game.h"
#include "Keyboard.h"

Simon::Simon()
{
	LPTEXTURE texture = Textures::GetInstance()->Get(SIMON_TEX_ID);

	//idle
	LPANIMATION s0 = new Animation(texture);
	s0->AddFrame(0, 0, 16, 32);
	AddAnimation(s0);

	//walk
	LPANIMATION s1 = new Animation(texture);
	s1->AddFrame(0, 0, 16, 32);
	s1->AddFrame(0, 32, 16, 32);
	s1->AddFrame(16, 32, 16, 32);
	s1->AddFrame(0, 32, 16, 32);
	AddAnimation(s1);

	//crounch
	LPANIMATION s2 = new Animation(texture);
	s2->AddFrame(0, 64, 16, 24);
	AddAnimation(s2);
	
	//attack1
	LPANIMATION s3 = new Animation(texture);
	s3->AddFrame(0, 96, 24, 32);
	s3->AddFrame(24, 96, 18, 32);
	s3->AddFrame(42, 96, 24, 32);
	AddAnimation(s3);

	//attack2
	LPANIMATION s4 = new Animation(texture);
	s4->AddFrame(0, 128, 24, 24);
	s4->AddFrame(24, 128, 18, 24);
	s4->AddFrame(42, 128, 24, 24);
	AddAnimation(s4);

	//hitted
	LPANIMATION s5 = new Animation(texture);
	s5->AddFrame(16, 64, 16, 32);
	AddAnimation(s5);

	//dead
	LPANIMATION s6 = new Animation(texture);
	s6->AddFrame(32, 64, 16, 32);
	s6->AddFrame(48, 64, 32, 16);
	AddAnimation(s6);

	SetAnimation(SIMON_IDLE_ANIMATION);
}

Simon::~Simon()
{
	//Animations* sprites = Animations::GetInstance();
	animations.clear();
}

void Simon::Update(DWORD dt, std::vector<LPGAMEOBJECT>* objects)
{
	GameObject::Update(dt);

	float dg = dt * GRAVITY;
	vy += dg;

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

		x += dx * min_tx + nx * (dg + 0.1f);
		y += dy * min_ty + ny * (dg+ 0.1f);

		if (nx != 0)
		{
			vx = 0;
		}
		if (ny != 0)
		{
			vy = 0;
		}
	}


}

void Simon::Render()
{
	int prevIndex = animations[currentAnimation]->CurrentFrameIndex();

	float X = x;
	float Y = y;

	LPSRPITE frame = animations[currentAnimation]->GetFrame();
	if (frame)
	{
		RECT r = frame->Rect;
		X += 16 - (r.right - r.left);
		Y += 32 - (r.bottom - r.top);
	}

	animations[currentAnimation]->Draw(X, Y, 255, flip);

	if (attack)
	{
		if (prevIndex == 2 && animations[currentAnimation]->CurrentFrameIndex() == 0)
		{
			attack = false;
			GoIdle();
		}
	}
}

void Simon::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + 16;
	b = t + 32;
}

void Simon::GoIdle()
{
	if (attack)
		return;

	if (!crounch)
	{
		SetAnimation(SIMON_IDLE_ANIMATION);
	}
	else SetAnimation(SIMON_CROUNCH_ANIMATION);
	vx = 0;
}


void Simon::GoLeft(bool active)
{
	if (attack)
		return;

	if (active)
	{
		SetAnimation(SIMON_WALK_ANIMATION);
		vx = -SIMON_SPEED;
		flip = false;
	}
	else
	{
		GoIdle();
	}
}

void Simon::GoRight(bool active)
{
	if (attack)
		return;

	if (active)
	{
		SetAnimation(SIMON_WALK_ANIMATION);
		vx = SIMON_SPEED;
		flip = true;
	}
	else
	{
		GoIdle();
	}
}

void Simon::Crounch(bool active)
{
	if (attack)
		return;

	if (active)
	{
		SetAnimation(SIMON_CROUNCH_ANIMATION);
		crounch = true;
		vx = 0;
	}
	else
	{
		crounch = false;
		GoIdle();
	}
}

void Simon::Jump()
{
	if (!jump)
	{
		vy = JUMP_FORCE;
		SetAnimation(SIMON_CROUNCH_ANIMATION);
	}
}

void Simon::Attack()
{

	if (crounch)
		SetAnimation(SIMON_ATTACK_2_ANIMATION);
	else
		SetAnimation(SIMON_ATTACK_1_ANIMATION);
	attack = true;
	vx = 0;
}