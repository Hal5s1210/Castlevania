#include "Item.h"
#include "Spawner.h"
#include "..\Scenes\Scene.h"
#include "..\..\Framework\Collision.h"


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

	float l, t, r, b;
	GetBoundingBox(l, t, r, b);

	Simon* player = Scenes::GetInstance()->GetScene()->GetPlayer();
	float pl, pt, pr, pb;
	player->GetBoundingBox(pl, pt, pr, pb);

	if (Collision::AABB(l, t, r, b, pl, pt, pr, pb))
	{
		if (!IsClaimed())
		{
			Board::GetInstance()->ItemClaimed(this);
			OutputDebugString(L"Claimed Item\n");
		}
	}

	vy += 0.00025 * dt;

	GameObject::CheckCollision(objects);
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

void Item::ProcessSweptAABBCollision(LPGAMEOBJECT o,
	float min_tx, float min_ty, float nx, float ny,
	float& dx, float& dy)
{
	if (dynamic_cast<Block*>(o))
	{

		dx = dx * min_tx + nx * 0.4f;
		dy = dy * min_ty + ny * 0.4f;

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

void Item::SetType(int t)
{
	switch (t)
	{
	case ITEM_WHIP_ID: type = eItem::Whip; break;
	case ITEM_DANGER_ID: type = eItem::Dagger; break;
	case ITEM_AXE_ID: type = eItem::Axe; break;
	case ITEM_BOOMERANG_ID: type = eItem::Boomerang; break;
	case ITEM_HOLYWATER_ID: type = eItem::HolyWater; break;
	case ITEM_STOPWATCH_ID: type = eItem::StopWatch; break;
	case ITEM_SMALLHEART_ID: type = eItem::SmallHeart; break;
	case ITEM_BIGHEART_ID: type = eItem::BigHeart; break;
	case ITEM_MONEY100_ID: type = eItem::Money100; break;
	case ITEM_MONEY400_ID: type = eItem::Money400; break;
	case ITEM_MONEY700_ID: type = eItem::Money700; break;
	case ITEM_MONEY1000_ID:	type = eItem::Money1000; break;
	case ITEM_CROWN_ID: type = eItem::Crown; break;
	case ITEM_CHEST_ID: type = eItem::Chest; break;
	case ITEM_ISLANDHEAD_ID: type = eItem::IslandHead; break;
	case ITEM_1UP_ID: type = eItem::LifeUp; break;
	case ITEM_PORK_ID: type = eItem::Pork; break;
	case ITEM_CROSS_ID: type = eItem::Cross; break;
	case ITEM_DOUBLESHOT_ID: type = eItem::DoubleShot; break;
	case ITEM_TRIPLESHOT_ID: type = eItem::TripleShot; break;
	case ITEM_CRYSTAL_ID: type = eItem::Crystall; break;
	case ITEM_INVISIBLE_ID: type = eItem::Invisible; break;

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

void Item::AddItem(int id, RECT r, float x, float y)
{
	LPITEM i = Spawner::GetInstance()->SpawnItem(id, x + ((r.right - r.left) / 2) - 4, y + ((r.bottom - r.top) / 2) - 8);
	Scenes::GetInstance()->GetScene()->AddItem(i);
}

void Item::SoundEffect()
{
	switch (type)
	{
	case Item::Whip:
	case Item::Dagger:
	case Item::Axe:
	case Item::Boomerang:
	case Item::StopWatch:
	case Item::HolyWater:
		Sound::GetInstance()->Play(SOUND_CLAIMWEAPON_ID);
		break;

	case Item::Money100:
	case Item::Money400:
	case Item::Money700:
	case Item::Money1000:
	case Item::Crown:
	case Item::Chest:
	case Item::IslandHead:
	case Item::Pork:
	case Item::DoubleShot:
	case Item::TripleShot:
	case Item::Invisible:
	case Item::Crystall:
		Sound::GetInstance()->Play(SOUND_CLAIMITEM_ID);
		break;

	case Item::SmallHeart:
	case Item::BigHeart:
		Sound::GetInstance()->Play(SOUND_CLAIMHEART_ID);
		break;

	case Item::LifeUp:
		Sound::GetInstance()->Play(SOUND_LIFEUP_ID);
		break;

	case Item::Cross:
		Sound::GetInstance()->Play(SOUND_CROSS_ID);
		break;

	default:
		break;
	}
}