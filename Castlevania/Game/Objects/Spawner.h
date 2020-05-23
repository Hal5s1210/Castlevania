#pragma once

#include <unordered_map>
#include "..\ID.h"
#include "GameObject.h"
#include "Simon.h"
#include "Others\Block.h"
#include "Others\Portal.h"
#include "Others\Candle.h"
#include "Others\Stair.h"
#include "Others\Background.h"
#include "Others\TitleEnter.h"
#include "Others\TitleBat.h"
#include "Others\BreakableBlock.h"
#include "Others\MovingBlock.h"
#include "Effect.h"
#include "Item.h"
#include "Enemies\Enemy.h"
#include "Enemies\VampireBat.h"
#include "Enemies\BlackKnight.h"
#include "Enemies\Ghost.h"
#include "Enemies\Hunchback.h"
#include "Enemies\WhiteSkeleton.h"
#include "Enemies\Zombie.h"
#include "Enemies\Raven.h"

class Spawner
{
private:
	static Spawner* _instance;
	std::unordered_map<int, LPGAMEOBJECT> objectSpawners;
	std::unordered_map<int, LPEFFECT> effectSpawners;
	std::unordered_map<int, LPITEM> itemSpawners;
	std::unordered_map<int, LPENEMY> enemySpawners;

public:
	Spawner();

	static Spawner* GetInstance();

	void CreateObjectSpawner(int id);
	void CreateEffectSpawner(int id);
	void CreateItemSpawner(int id);
	void CreateEnemySpawner(int id);

	LPGAMEOBJECT GetObjectSpawner(int id) { return objectSpawners[id]; }
	LPEFFECT GetEffectSpawner(int id) { return effectSpawners[id]; }
	LPITEM GetItemSpawner(int id) { return itemSpawners[id]; }
	LPENEMY GetEnemySpawner(int id) { return enemySpawners[id]; }

	LPGAMEOBJECT SpawnObject(int id, float x, float y, int item_id);
	LPEFFECT SpawnEffect(int id, float x, float y);
	LPITEM SpawnItem(int id, float x, float y);
	LPENEMY SpawnEnemy(int id, float x, float y, float l, float r, bool flip);
};

