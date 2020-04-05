#include "Spawner.h"
#include "..\Parser.h"

Spawner* Spawner::_instance = 0;

Spawner* Spawner::GetInstance()
{
	if (!_instance) _instance = new Spawner;
	return _instance;
}

void Spawner::CreateObjectSpawner(int id, pugi::xml_node root)
{
	LPGAMEOBJECT obj;

	switch (id)
	{
	case BLOCK_ID:
		obj = new Block;
		Parser::Parse_AnimationSet(obj, root);
		spawners[id] = obj;
		break;

	case TORCH_ID:
		obj = new Torch;
		Parser::Parse_AnimationSet(obj, root);
		spawners[id] = obj;
		break;

	case CANDLE_ID:
		obj = new Candle;
		Parser::Parse_AnimationSet(obj, root);
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