#include "Item.h"
#include "Spawner.h"
#include "..\Scenes\Scene.h"


Item::Item()
{
	claimed = false;
	timeOut = false;
	timerStart = GetTickCount();
	timeLimit = 5000;
}


void Item::Update(DWORD dt, std::vector<LPGAMEOBJECT>* objects)
{
	if (GetTickCount() - timerStart >= timeLimit)
	{
		timeOut = true;
		return;
	}

	GameObject::Update(dt);

	vy += 0.00025 * dt;

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
				ddy = dy * min_ty + ny * 0.4f;

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

		x += ddx;
		y += ddy;
	}
}

LPITEM Item::Clone()
{
	Item* clone = new Item;
	for (ANIMATION* ani : animations)
	{
		clone->AddAnimation(ani->first->Clone());
	}
	clone->SetAnimation(0);
	return clone;
}

void Item::Render(float x, float y)
{
	if (timeOut || claimed) return;
	currentAnimation->first->Draw(currentAnimation->second, this->x + x, this->y + y);
}

void Item::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	LPSPRITE s = currentAnimation->first->GetFrame(currentAnimation->second);
	RECT rect = s->GetRect();
	l = x;
	t = y;
	r = l + (rect.right - rect.left);
	b = t + (rect.bottom - rect.top);

}

void Item::SetType(int t)
{
	switch (t)
	{
	case ITEM_WHIP_ID: type = eItem::Whip; break;
	case ITEM_DANGER_ID: type = eItem::Dagger; break;
	case ITEM_AXE_ID: type = eItem::Axe; break;
	case ITEM_BOOMERANG_ID: type = eItem::Boomerang; break;
	case ITEM_HOLYWATER_ID: type = eItem::HolyWater; break;
	case ITEM_SMALLHEART_ID: type = eItem::SmallHeart; break;
	case ITEM_BIGHEART_ID: type = eItem::BigHeart; break;
	case ITEM_MONEY100_ID: type = eItem::Money100; break;
	case ITEM_MONEY400_ID: type = eItem::Money400; break;
	case ITEM_MONEY700_ID: type = eItem::Money700; break;
	case ITEM_MONEY1000_ID:	type = eItem::Money1000; break;

	default:
		type = eItem::Unknown;
		break;
	}
}

void Item::RunEffect(int id)
{
	if (id != 0)
	{
		int eff_x, eff_y;
		eff_x = x;
		eff_y = y;

		LPEFFECT effect = Spawner::GetInstance()->SpawnEffect(id, eff_x, eff_y);
		effect->SetTime(1000);
		Scenes::GetInstance()->GetScene()->AddEffect(effect);
	}
}

