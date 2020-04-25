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
	LPGAMEOBJECT obj;

	switch (id)
	{
	case TITLEBG_ID:
		obj = new Background;
		objectSpawners[id] = obj;
		break;

	case TITLEENTER_ID:
		obj = new TitleEnter;
		objectSpawners[id] = obj;
		break;

	case TITLEBAT_ID:
		obj = new TitleBat;
		objectSpawners[id] = obj;
		break;

	case TORCH_ID:
		obj = new Candle;
		objectSpawners[id] = obj;
		break;

	case CANDLE_ID:
		obj = new Candle;
		objectSpawners[id] = obj;
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