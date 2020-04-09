#include "Spawner.h"
#include "..\Parser.h"

Spawner* Spawner::_instance = 0;

Spawner::Spawner()
{
	LPGAMEOBJECT obj = new Block;
	spawners[BLOCK_ID] = obj;
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
	case TORCH_ID:
		obj = new Torch;
		spawners[id] = obj;
		break;

	case CANDLE_ID:
		obj = new Candle;
		spawners[id] = obj;
		break;

	default:
		break;
	}
}

LPGAMEOBJECT Spawner::SpawnObject(int id)
{
	return spawners[id]->Clone();
}