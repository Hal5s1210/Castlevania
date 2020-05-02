#include "Effect.h"
#include "..\..\Framework\Viewport.h"

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
	if (x < cam_x || x > cam_x + cam_w - 16 || y < cam_y || y> cam_y + cam_w - 16)
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