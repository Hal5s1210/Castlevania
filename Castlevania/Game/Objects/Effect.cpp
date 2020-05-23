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
		vy += 0.0005 * dt;
	}
	x += dx;
	y += dy;

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
}
void Effect::AddDeathEffect(RECT r, float x, float y)
{
	LPEFFECT e = Spawner::GetInstance()->SpawnEffect(EFFECT_DEAD_ID, x + ((r.right - r.left) / 2) - 4, y + ((r.bottom - r.top) / 2) - 8);
	Scenes::GetInstance()->GetScene()->AddEffect(e);
}