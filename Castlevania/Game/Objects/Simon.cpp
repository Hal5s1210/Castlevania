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
	on_air = true;
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

	if (on_moving_block)
	{
		vx += block_vx;
	}

	GameObject::Update(dt);


	if (auto_pilot)
	{
		AutoMove();

		if (reach_dest)
		{
			auto_pilot = false;
			reach_dest = false;
			if (use_stair)
			{
				flip = stair_dir_x == 1 ? true : false;
				state = stair_dir_y == 1 ? Simon::StairDown : Simon::StairUp;
				currentAnimation->second = 0;
				on_stair = true;
				step = false;
				step_done = false;
			}
		}

		if (!on_stair)
			return;

	}

	if (on_stair)
	{
		if (step)
		{
			float step_speed = 8.f / (200.f / dt) / dt;

			vx = stair_dir_x == 1 ? step_speed : -step_speed;
			vy = stair_dir_y == 1 ? step_speed : -step_speed;
		}
		else
		{
			vx = vy = 0;
		}
	}


	if (!on_stair)
	{
		vy += dt * GRAVITY;
		use_stair = false;
	}

	//check aabb
	for (LPGAMEOBJECT o : *objects)
	{
		float l, t, r, b;
		GetBoundingBox(l, t, r, b);

		if (dynamic_cast<Item*>(o))
		{
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
		else if (dynamic_cast<Stair*>(o))
		{
			Stair* s = dynamic_cast<Stair*>(o);

			float lo, to, ro, bo;
			o->GetBoundingBox(lo, to, ro, bo);

			if (Collision::AABB(l, t, r, b, lo, to, ro, bo))
			{
				if (!on_stair)
				{
					use_stair = true;

					s->GetDirection(stair_dir_x, stair_dir_y);
					s->GetPosition(auto_dest_x, auto_dest_y);
					auto_dest_y = y;
					auto_dir_x = x < auto_dest_x ? 1 : x == auto_dest_x ? 0 : -1;
				}
				else
				{
					int stair_dest_dir_x, stair_dest_dir_y;
					float stair_dest_pos_x, stair_dest_pos_y;
					s->GetDirection(stair_dest_dir_x, stair_dest_dir_y);
					s->GetPosition(stair_dest_pos_x, stair_dest_pos_y);

					if (stair_dir_x != stair_dest_dir_x && stair_dir_y != stair_dest_dir_y)
					{
						if ((stair_dir_x == 1 && r > ro) || (stair_dir_x == -1 && l < lo))
						{
							on_stair = false;
							use_stair = false;
							state = Simon::Idle;
							x = stair_dest_pos_x;
							y = stair_dest_pos_y - 16 - 0.4f;
						}
					}
				}
				
			}
		}
	}

	if (on_air && !on_stair)
	{
		vx = speed_before_jump;
	}

	//sweptaabb
	GameObject::CheckSweptCollision(objects);
	

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

	if (Debug::IsEnable())
	{
		float l, t, r, b;
		GetBoundingBox(l, t, r, b);
		Debug::RenderBoundBox(x, y, l, t, r, b);
	}

	if (on_stair)
	{
		if (!attack && currentAnimation->first->IsFrameReset())
		{
			currentAnimation->second = 1;
			currentAnimation->first->Pause();
			step = false;
			step_done = true;
		}
		else
		{
			currentAnimation->first->Play();
		}
	}

	if (attack)
	{
		whip->SetFrameIndex(i);
		whip->Render(x, y);

		if (currentAnimation->first->IsFrameReset())
		{
			whip->SetFrameIndex(0);
			attack = false;
			if (on_stair)
			{
				state = stair_dir_y == 1 ? Simon::StairDown : Simon::StairUp;
			}
			else state = Simon::Idle;
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

	l = X + 1;
	t = Y + 2;
	r = l + 16 - 2;
	b = t + 32 -2 - fixY;
}

void Simon::ProcessCollision(std::vector<LPCOEVENT>* coEventResults, 
	float min_tx, float min_ty, float nx, float ny, 
	float& dx, float& dy)
{
	for (LPCOEVENT coEvent : *coEventResults)
	{
		LPGAMEOBJECT o = coEvent->obj;

		if (dynamic_cast<Block*>(o) ||
			dynamic_cast<BreakableBlock*>(o))
		{
			if (on_stair) continue;
			if (dynamic_cast<BreakableBlock*>(o) && !dynamic_cast<BreakableBlock*>(o)->IsAlive()) continue;

			on_moving_block = false;

			dx = dx * min_tx + nx * 0.4f;
			if (ny == -1)dy = dy * min_ty + ny * 0.4f;

			if (nx != 0)
			{
				vx = 0;
			}

			if (ny != 0)
			{
				vy = 0;
				if (ny == -1)
				{
					if (on_air && attack)
					{
						vx = 0;
					}
					on_air = false;
				}
			}
		}
		else if (dynamic_cast<MovingBlock*>(o))
		{
			if (ny == -1)
			{
				dy = dy * min_ty + ny * 0.4f;

				vy = 0;
				if (on_air && attack)
				{
					vx = 0;
				}
				on_air = false;

				on_moving_block = true;

				float bvx, bvy;
				o->GetSpeed(bvx, bvy);
				block_vx = bvx;
			}
			else
			{
				on_moving_block = false;
			}
		}
		else if (dynamic_cast<Portal*>(o))
		{
			dynamic_cast<Portal*>(o)->Active();
		}
	}
}

void Simon::AutoMove()
{
	if (auto_dir_x == 0)
	{
		reach_dest = true;
	}
	else
	{
		x += dx;

		if ((auto_dir_x == 1 && x >= auto_dest_x)|| (auto_dir_x == -1 && x <= auto_dest_x))
		{
			x = auto_dest_x;
			reach_dest = true;
		}
	}
}


void Simon::SetState(eState state)
{
	if (hit || dead || auto_pilot)
		return;

	switch (state)
	{
	case Simon::Idle:
		if (attack || on_stair) break;
		if (on_air)
		{
			this->state = Simon::OnAir;
			break;
		}
		this->state = state;
		break;

	case Simon::WalkL:
	case Simon::WalkR:
		if (attack || on_stair) break;
		if (on_air)
		{
			this->state = Simon::OnAir;
			break;
		}
		this->state = state;
		break;

	case Simon::Crouch:
		if (attack || on_stair) break;
		if (on_air)
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
		if (attack || on_stair) break;
		this->state = state;
		break;

	case Simon::StairUp:
		if (use_stair && !on_air)
		{
			if (!on_stair)
			{
				if (stair_dir_y <= 0)
				{
					if (stair_dir_y == 0) stair_dir_y = -1;

					auto_pilot = true;
					this->state = auto_dir_x == 1 ? Simon::WalkR : Simon::WalkL;
				}
			}
			else
			{
				if (!step && currentAnimation->first->IsFrameReset())
				{
					step_done = false;

					if (stair_dir_y == 1) change_dir = true;

					this->state = Simon::StairUp;
				}
			}
		}
		break;

	case Simon::StairDown:
		if (use_stair && !on_air)
		{
			if (!on_stair)
			{
				if (stair_dir_y >= 0)
				{
					if (stair_dir_y == 0) stair_dir_y = 1;

					auto_pilot = true;
					this->state = auto_dir_x == 1 ? Simon::WalkR : Simon::WalkL;
				}
			}
			else
			{
				if (!step && currentAnimation->first->IsFrameReset())
				{
					step_done = false;

					if (stair_dir_y == -1) change_dir = true;

					this->state = Simon::StairDown;
				}
			}
		}
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
		currentAnimation->first->Play();
		crouch = false;
		vx = 0;
		break;

	case Simon::WalkL:
		SetAnimation(WALK);
		currentAnimation->first->Play();
		vx = -SIMON_SPEED;
		crouch = false;
		flip = false;
		break;

	case Simon::WalkR:
		SetAnimation(WALK);
		currentAnimation->first->Play();
		vx = SIMON_SPEED;
		crouch = false;
		flip = true;
		break;

	case Simon::Crouch:
		SetAnimation(CROUNCH);
		currentAnimation->first->Play();
		crouch = true;
		vx = 0;
		break;

	case Simon::Attack:
		if (!attack)
		{
			whip->UseWhip(true);

			if (on_stair)
			{
				if (step_done)
				{
					if (stair_dir_y == 1)
						SetAnimation(STAIR_DOWN_ATTACK);
					else
						SetAnimation(STAIR_UP_ATTACK);

					currentAnimation->second = -1;
					currentAnimation->first->Play();
					attack = true;
				}
			}
			else
			{
				if (crouch)
					SetAnimation(ATTACK_2);
				else
					SetAnimation(ATTACK_1);
				currentAnimation->second = -1;
				currentAnimation->first->Play();
				crouch = false;
				attack = true;
				if (!on_air) vx = 0;
			}
		}
		break;

	case Simon::SubAttack:
		if (!subweapon->IsUsable()) break;
		if (!attack)
		{
			if (!on_stair)
			{
				whip->UseWhip(false);

				subweapon->Active();

				if (crouch)
					SetAnimation(ATTACK_2);
				else
					SetAnimation(ATTACK_1);
				currentAnimation->second = -1;
				currentAnimation->first->Play();
				crouch = false;
				attack = true;
				if (!on_air) vx = 0;
			}
		}
		break;

	case Simon::Jump:
		if (!on_air)
		{
			vy = JUMP_FORCE;
			speed_before_jump = vx;
			jumpStartTime = GetTickCount();
			crouch = false;
			on_air = true;
			SetAnimation(CROUNCH);
			currentAnimation->first->Play();
		}
		break;

	case Simon::OnAir:
		if (on_air)
		{
			SetAnimation(CROUNCH);
			currentAnimation->first->Play();
		}
		break;

	case Simon::StairUp:
		if (on_stair)
		{
			SetAnimation(STAIR_UP);
			if (!step && !step_done)
			{
				step = true;
				if (change_dir)
				{
					stair_dir_x = -stair_dir_x;
					stair_dir_y = -stair_dir_y;
					flip = !flip;
					change_dir = false;
				}

				currentAnimation->first->Play();
				currentAnimation->second = -1;
			}
		}
		break;

	case Simon::StairDown:
		if (on_stair)
		{
			SetAnimation(STAIR_DOWN);
			if (!step && !step_done)
			{
				step = true;
				if (change_dir)
				{
					stair_dir_x = -stair_dir_x;
					stair_dir_y = -stair_dir_y;
					flip = !flip;
					change_dir = false;
				}

				currentAnimation->first->Play();
				currentAnimation->second = -1;
			}
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