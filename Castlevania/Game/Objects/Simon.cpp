#include "Simon.h"
#include "..\..\Framework\Game.h"

Simon::Simon()
{
	LPTEXTURE texture = Textures::GetInstance()->Get(TEXTURE_SIMON_ID);

	//idle
	LPANIMATION s0 = new Animation(texture);
	s0->AddFrame(0, 0, 16, 32);
	AddAnimation("idle", s0);

	//walk
	LPANIMATION s1 = new Animation(texture);
	s1->AddFrame(0, 0, 16, 32);
	s1->AddFrame(0, 32, 16, 32);
	s1->AddFrame(16, 32, 16, 32);
	s1->AddFrame(0, 32, 16, 32);
	AddAnimation("walk", s1);

	//crounch
	LPANIMATION s2 = new Animation(texture);
	s2->AddFrame(0, 64, 16, 24);
	AddAnimation("crounch", s2);

	//attack1
	LPANIMATION s3 = new Animation(texture);
	s3->AddFrame(0, 96, 24, 32, 50);
	s3->AddFrame(24, 96, 18, 32, 50);
	s3->AddFrame(48, 96, 18, 32, 50);
	AddAnimation("attack1", s3);

	//attack2
	LPANIMATION s4 = new Animation(texture);
	s4->AddFrame(0, 128, 24, 24, 50);
	s4->AddFrame(24, 128, 18, 24, 50);
	s4->AddFrame(48, 128, 18, 24, 50);
	AddAnimation("attack2", s4);

	//hitted
	LPANIMATION s5 = new Animation(texture);
	s5->AddFrame(16, 64, 16, 32);
	AddAnimation("hitted", s5);

	//dead
	LPANIMATION s6 = new Animation(texture);
	s6->AddFrame(32, 64, 16, 32);
	s6->AddFrame(48, 64, 32, 16);
	AddAnimation("dead", s6);

	SetAnimation("idle");
	attack = false;
	crounch = false;
	onair = true;

}
Simon::~Simon()
{
}

void Simon::Update(DWORD dt, std::vector<LPGAMEOBJECT>* objects)
{
	GameObject::Update(dt);

	 vy += dt * GRAVITY;

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

		x += dx * min_tx + nx * 0.4f;
		if(onair) 
			y += dy * min_ty + ny * 0.4f;

		if (nx != 0)
		{
			vx = 0;
		}
		if (ny != 0)
		{
			vy = 0;
			if (ny == -1) onair = false;
			//GoIdle();
		}
	}

	Viewport::GetInstance()->SetPosition(x - 112, 0);
}

void Simon::Render(float x, float y)
{
	float X = this->x + x;
	float Y = this->y + y;

	LPSRPITE frame = currentAnimation->GetFrame();
	RECT r = frame->Rect;
	if (flip) X += 16 - (r.right - r.left);
	Y += 32 - (r.bottom - r.top);

	currentAnimation->Draw(X, Y, 255, flip);

	if (attack)
	{
		if (currentAnimation->CurrentFrameIndex() == -1)
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

	if (onair)
	{
		SetAnimation("crounch");
	}
	else
	{
		SetAnimation("idle");
		vx = 0;
	}
}


void Simon::GoLeft()
{
	if (attack || onair)
		return;

	SetAnimation("walk");
	vx = -SIMON_SPEED;
	flip = false;
	
}

void Simon::GoRight()
{
	if (attack || onair)
		return;

	SetAnimation("walk");
	vx = SIMON_SPEED;
	flip = true;
}

void Simon::Crounch()
{
	if (attack || onair)
		return;

	SetAnimation("crounch");
	vx = 0;
}

void Simon::Jump()
{
	if (!onair)
	{
		vy = JUMP_FORCE;
		onair = true;
		SetAnimation("crounch");
	}
}

void Simon::Attack(bool crounch)
{
	if (crounch && !onair)
		SetAnimation("attack2");
	else
		SetAnimation("attack1");
	attack = true;
	if (!onair) vx = 0;
}

void Simon::SubAttack()
{
	SetAnimation("attack1");
	attack = true;
	if (!onair) vx = 0;
}