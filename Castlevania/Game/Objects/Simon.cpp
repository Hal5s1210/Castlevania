#include "Simon.h"
#include "Spawner.h"

Simon::Simon()
{
	whip = new Whip;
	flip = true;
	attack = false;
	crounch = false;
	onair = true;
	jumpStartTime = -1;
	state = Simon::Idle;
}

Simon::~Simon()
{
	delete whip;
}


void Simon::Update(DWORD dt, std::vector<LPGAMEOBJECT>* objects)
{
	ProcessState();

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

		float ddx, ddy;

		ddx = dx;
		ddy = dy;

		for (LPCOEVENT coEvent : coEventResults)
		{
			LPGAMEOBJECT o = coEvent->obj;

			if (dynamic_cast<Block*>(o))
			{
				ddx = dx * min_tx + nx * 0.4f;
				if(ny == -1)ddy = dy * min_ty + ny * 0.4f;

				if (nx != 0)
				{
					vx = 0;
				}

				if (ny == -1)
				{
					vy = 0;
					if (onair && attack)
					{
						vx = 0;
					}
					onair = false;
				}
			}
			else
			{
				ddx = dx;
				ddy = dy;
			}
		}

		x += ddx;
		y += ddy;

	}

	if (attack)
	{
		float whip_x = x;
		float whip_y = y;

		LPSPRITE sprite = currentAnimation->first->GetFrame(currentAnimation->second);
		RECT rect = sprite->GetRect();
		if (flip) whip_x += 16;
		whip_y += 32 - (rect.bottom - rect.top);

		whip->SetPosition(whip_x, whip_y);
		whip->SetFlip(flip);

		whip->Update(dt, objects);
	}


	//float cam_x, cam_y;
	//int cam_w, cam_h;
	//Viewport::GetInstance()->GetPosition(cam_x, cam_y);
	//Viewport::GetInstance()->GetSize(cam_w, cam_h);
	//if (x < cam_x)
	//{
	//	x = cam_x;
	//	vx = 0;
	//}
	//else if (x > cam_x + cam_w - 16)
	//{
	//	x = cam_x + cam_h;
	//	vx = 0;
	//
	//}
}

void Simon::Render(float x, float y)
{
	float X = this->x + x;
	float Y = this->y + y;

	int i = currentAnimation->second;
	LPSPRITE sprite = currentAnimation->first->GetFrame(currentAnimation->second);
	RECT rect = sprite->GetRect();
	float fixX = 16 - (rect.right - rect.left);
	float fixY = 32 - (rect.bottom - rect.top);
	if (flip) X += fixX;
	Y += fixY;

	currentAnimation->first->Draw(currentAnimation->second, X, Y, 255, flip);

	float l, t, r, b;
	GetBoundingBox(l, t, r, b);
	NSDebug::RenderBoundBox(x, y, l, t, r, b);

	if (attack)
	{
		whip->SetFrameIndex(i);
		whip->Render(x, y);

		if (currentAnimation->first->IsFrameReset())
		{
			attack = false;
		}
	}
	
}

void Simon::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	float X = this->x;
	float Y = this->y;

	LPSPRITE sprite = currentAnimation->first->GetFrame(currentAnimation->second);
	RECT rect = sprite->GetRect();
	float fixX = 16 - (rect.right - rect.left);
	float fixY = 32 - (rect.bottom - rect.top);
	Y += fixY;

	l = X;
	t = Y;
	r = l + 16;
	b = t + 32 - fixY;
}

void Simon::SetState(eState state)
{
	if (hitted || dead)
		return;

	switch (state)
	{
	case Simon::Idle:
		if (attack) break;
		if (onair)
		{
			this->state = Simon::OnAir;
			break;
		}
		this->state = state;
		break;

	case Simon::WalkL:
	case Simon::WalkR:
		if (attack) break;
		if (onair)
		{
			this->state = Simon::OnAir;
			break;
		}
		this->state = state;
		break;

	case Simon::Crounch:
		if (attack) break;
		if (onair)
		{
			this->state = Simon::OnAir;
			break;
		}
		this->state = state;
		break;
		
	case Simon::Attack:
		this->state = state;
		break;

	case Simon::Jump:
		if (attack) break;
		this->state = state;
		break;

	default:
		this->state = state;
		break;
	}
}

void Simon::ProcessState()
{
	switch (state)
	{
	case Simon::Idle:
		SetAnimation(IDLE);
		crounch = false;
		vx = 0;
		break;

	case Simon::WalkL:
		SetAnimation(WALK);
		vx = -SIMON_SPEED;
		crounch = false;
		flip = false;
		break;

	case Simon::WalkR:
		SetAnimation(WALK);
		vx = SIMON_SPEED;
		crounch = false;
		flip = true;
		break;

	case Simon::Crounch:
		SetAnimation(CROUNCH);
		crounch = true;
		vx = 0;
		break;

	case Simon::Attack:
		if (!attack)
		{
			whip->UseWhip(true);
			if (crounch)
				SetAnimation(ATTACK_2);
			else
				SetAnimation(ATTACK_1);
			currentAnimation->second = -1;
			crounch = false;
			attack = true;
			if (!onair) vx = 0;
		}
		break;

	case Simon::SubWeapon:
		if (!attack)
		{
			whip->UseWhip(false);
			if (crounch)
				SetAnimation(ATTACK_2);
			else
				SetAnimation(ATTACK_1);
			currentAnimation->second = -1;
			crounch = false;
			attack = true;
			if (!onair) vx = 0;
		}
		break;

	case Simon::Jump:
		if (!onair)
		{
			vy = JUMP_FORCE;
			jumpStartTime = GetTickCount();
			crounch = false;
			onair = true;
			SetAnimation(CROUNCH);
		}
		break;

	case Simon::OnAir:
		if (onair)
		{
			SetAnimation(CROUNCH);
		}
		break;

	case Simon::Hitted:
		break;
	case Simon::Dead:
		break;
	default:
		break;
	}
}