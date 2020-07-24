#include "PhantomBat.h"
#include "..\..\..\Scenes\Scene.h"

PhantomBat::PhantomBat()
{
	score = 10000;
	readytime = 3000;
	movetime = 1000;
	attacktime = 2000;
	reach_des = true;
	attack = false;
}
Enemy* PhantomBat::Clone()
{
	PhantomBat* clone = new PhantomBat;
	for (ANIMATION* ani : animations)
	{
		clone->AddAnimation(ani->first->Clone());
	}
	clone->SetAnimation(0);
	return clone;
}

void PhantomBat::Active()
{
	Enemy::Active();
	readytimestart = -1;
	movetimestart = -1;
}

void PhantomBat::Unactive()
{
	Enemy::Unactive();
	awake = false;
	flying = false;
	reach_des = true;
	attack = false;
}

void PhantomBat::Brain(DWORD dt)
{
	srand((unsigned)time(NULL));

	Simon* player = Scenes::GetInstance()->GetScene()->GetPlayer();
	float p_x, p_y;
	player->GetPosition(p_x, p_y);

	if (!awake && p_x >= activeL && p_x <= activeR)
	{
		awake = true;
	}

	if (awake)
	{
		if (!flying)
		{
			DWORD now = GetTickCount();
			if (readytimestart == -1) readytimestart = now;
			if (now - readytimestart > readytime)
			{
				flying = true;
				readytimestart = -1;
				SetAnimation(1);
				float cam_x, cam_y;
				Viewport::GetInstance()->GetPosition(cam_x, cam_y);
				positions.push_back(std::pair<float, float>(cam_x + 72, cam_y + 56));
				positions.push_back(std::pair<float, float>(cam_x + 168, cam_y + 56));
				positions.push_back(std::pair<float, float>(cam_x + 120, cam_y + 88));
				positions.push_back(std::pair<float, float>(cam_x + 40, cam_y + 104));
				positions.push_back(std::pair<float, float>(cam_x + 200, cam_y + 104));
				return;
			}
			return;
		}

		if (reach_des)
		{
			if (movetimestart == -1)
			{
				int i;
				do {
					i = rand() % 5;
				} while (i == pos);
				pos = i;
				pos_x = positions[pos].first;
				pos_y = positions[pos].second;
				movetimestart = GetTickCount();
			}
			else
			{
				if (GetTickCount() - movetimestart > movetime)
				{
					if (!attack) GoTo(pos_x, pos_y);
					else
					{
						atk_start_x = x;
						atk_start_y = y;
						atk_end_x = p_x;
						atk_end_y = p_y;
						attacktimestart = GetTickCount();
						reach_des = false;
					}
					movetimestart = -1;
				}
			}
		}
		else
		{
			if (!attack)
			{
				x += vx * dt;
				y += vy * dt;

				if ((vx > 0 && vy > 0 && x > des_x && y > des_y) ||
					(vx > 0 && vy < 0 && x > des_x && y < des_y) ||
					(vx < 0 && vy > 0 && x < des_x && y > des_y) ||
					(vx < 0 && vy < 0 && x < des_x && y < des_y))
				{
					reach_des = true;
					attack = true;
					x = des_x;
					y = des_y;
					vx = vy = 0;
				}
			}
			else
			{
				if (GetTickCount() - attacktimestart < attacktime)
				{
					GoInParabola(pos_x, pos_y);

					float cam_x, cam_y;
					int cam_w, cam_h;
					Viewport::GetInstance()->GetPosition(cam_x, cam_y);
					Viewport::GetInstance()->GetSize(cam_w, cam_h);
					if (x < cam_x)
					{
						x = cam_x;
						attack = false;
						reach_des = true;
						vx = vy = 0;
					}
					if (x > cam_x + cam_w - 32)
					{
						x = cam_x + cam_w - 32;
						attack =  false;
						reach_des = true;
						vx = vy = 0;
					}
					if (y < cam_y + 16)
					{
						y = cam_y + 16;
						attack = false;
						reach_des = true;
						vx = vy = 0;
					}
				}
				else
				{
					attack = false;
					reach_des = true;
					vx = vy = 0;
				}
			}
		}
	}
	
}

void PhantomBat::GoTo(float desx, float desy)
{
	des_x = desx;
	des_y = desy;
	float d_x = abs(des_x - x);
	float d_y = abs(des_y - y);
	float alpha = atan((double)(d_y / d_x));
	float speed = 0.05;
	vx = des_x > x ? cos(alpha) * speed : -cos(alpha) * speed;
	vy = des_y > y ? sin(alpha) * speed : -sin(alpha) * speed;
	reach_des = false;
}


void PhantomBat::GoInParabola(float desx, float desy)
{
	float a = (atk_end_y - atk_start_y) / pow((atk_end_x - atk_start_x), 2);
	float speed = 0.05 * pow(abs(atk_end_x - atk_start_x) / 128, 2) + 0.01;
	vx = atk_end_x > atk_start_x ? speed : -speed;
	x += vx * dt;
	y = -a * pow(x - atk_end_x, 2) + atk_end_y;
}

void PhantomBat::Render(float x, float y)
{
	if (!active) return;
	if (!alive || outview) return;

	float X, Y;
	LPSPRITE sprite = currentAnimation->first->GetFrame(currentAnimation->second);
	RECT rect = sprite->GetRect();
	int w = rect.right - rect.left;
	X = this->x + 8 - w / 2;
	Y = this->y;

	currentAnimation->first->Draw(currentAnimation->second, X + x, Y + y, 255, flip);

	if (Debug::IsEnable())
	{
		float l, t, r, b;
		GetBoundingBox(l, t, r, b);
		Debug::RenderBoundBox(x, y, l, t, r, b);
	}
}

void PhantomBat::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (!awake) return;

	LPSPRITE sprite = currentAnimation->first->GetFrame(currentAnimation->second);
	RECT rect = sprite->GetRect();
	int w = rect.right - rect.left;
	int h = rect.bottom - rect.top;

	l = x + 8 - w / 2;
	r = l + w;
	t = y;
	b = t + h;
}

void PhantomBat::ProcessAABBCollision(LPGAMEOBJECT o)
{
	if (dynamic_cast<Simon*>(o))
	{
		Simon* player = dynamic_cast<Simon*>(o);
		player->TakeHit(2);
	}
}