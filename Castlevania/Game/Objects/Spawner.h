#pragma once

#include <unordered_map>
#include "..\ID.h"
#include "GameObject.h"
#include "Simon.h"
#include "Others\Block.h"
#include "Others\Torch.h"
#include "Others\Candle.h"
#include "Effect.h"
#include "Item.h"

class Spawner
{
private:
	static Spawner* _instance;
	std::unordered_map<int, LPGAMEOBJECT> objectSpawners;
	std::unordered_map<int, LPEFFECT> effectSpawners;
	std::unordered_map<int, LPITEM> itemSpawners;

public:
	Spawner();

	static Spawner* GetInstance();

	void CreateObjectSpawner(int id);
	void CreateEffectSpawner(int id);
	void CreateItemSpawner(int id);

	LPGAMEOBJECT GetObjectSpawner(int id) { return objectSpawners[id]; }
	LPEFFECT GetEffectSpawner(int id) { return effectSpawners[id]; }
	LPITEM GetItemSpawner(int id) { return itemSpawners[id]; }

	LPGAMEOBJECT SpawnObject(int id, float x, float y, int item_id);
	LPEFFECT SpawnEffect(int id, float x, float y);
	LPITEM SpawnItem(int id, float x, float y);
};

