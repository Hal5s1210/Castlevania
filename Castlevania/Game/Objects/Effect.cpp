#include "Effect.h"
#include "..\..\Framework\Viewport.h"
#include "Spawner.h"
#include "..\Scenes\Scene.h"

LPEFFECT Effect::Clone()
{
	Effect* clone = new Effect;
	for (ANIMATION* ani : animations)
	{
		clone->AddAnimation(ani->first->Clone());
	}
	clone->SetAnimation(0);
	return clone;
}

void Effect::Update(DWORD dt)
{
	GameObject::Update(dt);
	if (gravity)
	{
		vy += 0.001 * dt;
	}

	x += vx * dt;
	y += vy * dt;

	float cam_x, cam_y;
	int cam_w, cam_h;
	Viewport::GetInstance()->GetSize(cam_w, cam_h);
	Viewport::GetInstance()->GetPosition(cam_x, cam_y);
	if (x < cam_x || x > cam_x + cam_w - 8 || y < cam_y || y> cam_y + cam_w - 8)
	{
		outView = true;
	}
}

void Effect::Render(float x, float y)
{
	SetAnimation(0);
	currentAnimation->first->Draw(currentAnimation->second, this->x + x, this->y + y);

	if (time == 0)
	{
		if (currentAnimation->first->IsFrameReset())
		{
			done = true;
		}
	}
	else
	{
		if (GetTickCount() - startTime >= time)
		{
			done = true;
		}
	}
}

void Effect::AddHitEffect(LPGAMEOBJECT hitter, LPGAMEOBJECT obj)
{
	if (hitter == NULL || obj == NULL) return;
	//hitter bbox
	float lh, th, rh, bh;
	hitter->GetBoundingBox(lh, th, rh, bh);
	//object bbox
	float lo, to, ro, bo;
	obj->GetBoundingBox(lo, to, ro, bo);

	int eff_x, eff_y;
	if (hitter->IsFlip()) eff_x = ro - (rh - lh) / 2;
	else eff_x = lo + (rh - lh) / 2;
	eff_y = to + (bh - th) / 2;

	LPEFFECT effect = Spawner::GetInstance()->SpawnEffect(EFFECT_HIT_ID, eff_x, eff_y);
	Scenes::GetInstance()->GetScene()->AddEffect(effect);
	Sound::GetInstance()->Play(SOUND_HITEFFECT_ID);
}

void Effect::AddDeathEffect(RECT r, float x, float y)
{
	LPEFFECT e = Spawner::GetInstance()->SpawnEffect(EFFECT_DEAD_ID, x + ((r.right - r.left) / 2) - 4, y + ((r.bottom - r.top) / 2) - 8);
	Scenes::GetInstance()->GetScene()->AddEffect(e);
	Sound::GetInstance()->Play(SOUND_DEATHEFFECT_ID);
}

void Effect::AddBossDeathEffect(RECT r, float x, float y)
{
	AddDeathEffect(r, x - 8, y - 16);
	AddDeathEffect(r, x, y - 16);
	AddDeathEffect(r, x + 8, y - 16);
	AddDeathEffect(r, x - 8, y);
	AddDeathEffect(r, x, y);
	AddDeathEffect(r, x + 8, y);
	AddDeathEffect(r, x - 8, y + 16);
	AddDeathEffect(r, x, y + 16);
	AddDeathEffect(r, x + 8, y + 16);
}

void Effect::AddBreakBlockEffect(RECT r, float x, float y)
{
	LPEFFECT e1 = Spawner::GetInstance()->SpawnEffect(EFFECT_BROKENBLOCK_ID, x + ((r.right - r.left) / 2), y + ((r.bottom - r.top) / 2));
	e1->SetSpeed(-0.04, -0.4);
	e1->UseGravity();
	e1->OnetimeEffect(false);
	LPEFFECT e2 = Spawner::GetInstance()->SpawnEffect(EFFECT_BROKENBLOCK_ID, x + ((r.right - r.left) / 2), y + ((r.bottom - r.top) / 2));
	e2->SetSpeed(0.04, -0.3);
	e2->UseGravity();
	e2->OnetimeEffect(false);
	LPEFFECT e3 = Spawner::GetInstance()->SpawnEffect(EFFECT_BROKENBLOCK_ID, x + ((r.right - r.left) / 2), y + ((r.bottom - r.top) / 2));
	e3->SetSpeed(-0.02, -0.45);
	e3->UseGravity();
	e3->OnetimeEffect(false);

	Scenes::GetInstance()->GetScene()->AddEffect(e1);
	Scenes::GetInstance()->GetScene()->AddEffect(e2);
	Scenes::GetInstance()->GetScene()->AddEffect(e3);

	Sound::GetInstance()->Play(SOUND_DEATHEFFECT_ID);
}



bool Effect::flash = false;
int Effect::flashcount = 0;

void Effect::RenderBackgroundEffect()
{
	if (flash)
	{
		if (flashcount % 2 == 0)
			Graphics::GetInstance()->FillColor(255, 255, 255);

		flashcount++;
		if (flashcount > 6)
		{
			flash = false;
			flashcount = 0;
		}
	}
}

void Effect::Flash()
{
	flash = true;
}