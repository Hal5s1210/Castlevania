#include "Spawner.h"
#include "..\Parser.h"

Spawner* Spawner::_instance = 0;

Spawner::Spawner()
{
}


Spawner* Spawner::GetInstance()
{
	if (!_instance) _instance = new Spawner;
	return _instance;
}

void Spawner::CreateObjectSpawner(int id)
{
	LPGAMEOBJECT o;
	switch (id)
	{
	case TITLEBG_ID:
		o = new Background;
		objectSpawners[id] = o;
		break;

	case TITLEENTER_ID:
		o = new TitleEnter;
		objectSpawners[id] = o;
		break;

	case TITLEBAT_ID:
		o = new TitleBat;
		objectSpawners[id] = o;
		break;

	case TORCH_ID:
	case CANDLE_ID:
		o = new Candle;
		objectSpawners[id] = o;
		break;

	case BREAKABLEBLOCK_S2_ID:
	case BREAKABLEBLOCK_S3_ID:
	case BREAKABLEBLOCK_S4_ID:
		o = new BreakableBlock;
		objectSpawners[id] = o;
		break;

	case MOVINGBLOCK_ID:
		o = new MovingBlock;
		objectSpawners[id] = o;
		break;

	default:
		break;
	}
}
LPGAMEOBJECT Spawner::SpawnObject(int id, float x, float y, int item_id)
{
	LPGAMEOBJECT o = objectSpawners[id]->Clone();
	o->SetPosition(x, y);

	if (item_id != 0)
	{
		switch (id)
		{
		case TORCH_ID:
		case CANDLE_ID:
			dynamic_cast<Candle*>(o)->HoldItem(item_id);
			break;

		default:
			break;
		}
	}

	return o;
}

void Spawner::CreateEffectSpawner(int id)
{
	LPEFFECT effect;
	effect = new Effect;
	effectSpawners[id] = effect;
}
LPEFFECT Spawner::SpawnEffect(int id, float x, float y)
{
	LPEFFECT e = effectSpawners[id]->Clone();
	e->SetPosition(x, y);

	return e;
}


void Spawner::CreateItemSpawner(int id)
{
	LPITEM item;
	item = new Item;
	itemSpawners[id] = item;
}
LPITEM Spawner::SpawnItem(int id, float x, float y)
{
	LPITEM i = itemSpawners[id]->Clone();
	i->SetPosition(x, y);
	i->SetType(id);

	return i;
}

void Spawner::CreateEnemySpawner(int id)
{
	LPENEMY o;
	switch (id)
	{
	case VAMPIREBAT_ID:
		o = new VampireBat;
		enemySpawners[id] = o;
		break;

	case BLACKKNIGHT_ID:
		o = new BlackKnight;
		enemySpawners[id] = o;
		break;

	case GHOST_ID:
		o = new Ghost;
		enemySpawners[id] = o;
		break;

	case HUNCHBACK_ID:
		o = new Hunchback;
		enemySpawners[id] = o;
		break;

	case WHITESKELETON_ID:
		o = new WhiteSkeleton;
		enemySpawners[id] = o;
		break;

	case RAVEN_ID:
		o = new Raven;
		enemySpawners[id] = o;
		break;

	case ZOMBIE_ID:
		o = new Zombie;
		enemySpawners[id] = o;
		break;

	default:
		break;
	}
}
LPENEMY Spawner::SpawnEnemy(int id, float x, float y ,float l, float r, bool flip)
{
	LPENEMY e = enemySpawners[id]->Clone();
	e->SetDefaultPosition(x, y);
	e->SetDefaultFlip(flip);
	e->SetActiveLR(l, r);
	
	return e;
}
