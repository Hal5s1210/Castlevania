#include "Simon.h"
#include "Spawner.h"
#include "..\Board.h"
#include "..\..\Framework\Collision.h"
#include "..\..\Framework\Viewport.h"

Simon::Simon()
{
	whip = new Whip;
	subweapon = new SubWeapon(this);
	flip = true;
	attack = false;
	crouch = false;
	onair = true;
	jumpStartTime = -1;
	state = Simon::Idle;
}

Simon::~Simon()
{
	delete whip;
	delete subweapon;
}


void Simon::Update(DWORD dt, std::vector<LPGAMEOBJECT>* objects)
{
	Board::GetInstance()->GetSimonData(whip, subweapon);

	ProcessState();

	GameObject::Update(dt);

	vy += dt * GRAVITY;

	//check aabb
	for (LPGAMEOBJECT o : *objects)
	{
		if (dynamic_cast<Item*>(o))
		{
			float l, t, r, b;
			GetBoundingBox(l, t, r, b);
			float lo, to, ro, bo;
			o->GetBoundingBox(lo, to, ro, bo);

			if (Collision::AABB(l, t, r, b, lo, to, ro, bo))
			{
				LPITEM item = dynamic_cast<Item*>(o);
				if (!item->IsClaimed())
				{
					Board::GetInstance()->ItemClaimed(item);
					OutputDebugString(L"Claimed Item\n");
				}
			}
		}
	}


	//sweptaabb
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

				if (ny != 0)
				{
					vy = 0;
					if (ny == -1)
					{
						if (onair && attack)
						{
							vx = 0;
						}
						onair = false;
					}
				}
			}
			else if (dynamic_cast<Portal*>(o))
			{
				dynamic_cast<Portal*>(o)->Active();
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
	
	if (subweapon->IsReady())
	{
		float sub_x = x;
		float sub_y = y + 4;

		LPSPRITE sprite = currentAnimation->first->GetFrame(currentAnimation->second);
		RECT rect = sprite->GetRect();
		if (flip) sub_x += 16;
		sub_y += 32 - (rect.bottom - rect.top);

		subweapon->AddWeapon(flip, sub_x, sub_y);
	}

	subweapon->Update(dt, objects);


	float cam_x, cam_y;
	int cam_w, cam_h;
	Viewport::GetInstance()->GetPosition(cam_x, cam_y);
	Viewport::GetInstance()->GetSize(cam_w, cam_h);
	if (x < cam_x)
	{
		x = cam_x;
		vx = 0;
	}
	else if (x > cam_x + cam_w - 16)
	{
		x = cam_x + cam_w - 16;
		vx = 0;
	
	}
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

	subweapon->Render(x, y);

	//float l, t, r, b;
	//GetBoundingBox(l, t, r, b);
	//NSDebug::RenderBoundBox(x, y, l, t, r, b);

	if (attack)
	{
		whip->SetFrameIndex(i);
		whip->Render(x, y);

		if (currentAnimation->first->IsFrameReset())
		{
			whip->SetFrameIndex(0);
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
	if (hit || dead)
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

	case Simon::Crouch:
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
		crouch = false;
		vx = 0;
		break;

	case Simon::WalkL:
		SetAnimation(WALK);
		vx = -SIMON_SPEED;
		crouch = false;
		flip = false;
		break;

	case Simon::WalkR:
		SetAnimation(WALK);
		vx = SIMON_SPEED;
		crouch = false;
		flip = true;
		break;

	case Simon::Crouch:
		SetAnimation(CROUNCH);
		crouch = true;
		vx = 0;
		break;

	case Simon::Attack:
		if (!attack)
		{
			whip->UseWhip(true);

			if (crouch)
				SetAnimation(ATTACK_2);
			else
				SetAnimation(ATTACK_1);
			currentAnimation->second = -1;
			crouch = false;
			attack = true;
			if (!onair) vx = 0;
		}
		break;

	case Simon::SubAttack:
		if (!subweapon->IsUsable()) break;
		if (!attack)
		{
			whip->UseWhip(false);

			subweapon->Active();

			if (crouch)
				SetAnimation(ATTACK_2);
			else
				SetAnimation(ATTACK_1);
			currentAnimation->second = -1;
			crouch = false;
			attack = true;
			if (!onair) vx = 0;
		}
		break;

	case Simon::Jump:
		if (!onair)
		{
			vy = JUMP_FORCE;
			jumpStartTime = GetTickCount();
			crouch = false;
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