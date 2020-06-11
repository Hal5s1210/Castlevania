#pragma once

#include <unordered_map>
#include "..\ID.h"
#include "GameObject.h"

#include "Simon.h"

#include "Others\Block.h"
#include "Others\Portal.h"
#include "Others\Candle.h"
#include "Others\Stair.h"
#include "Others\BreakableBlock.h"
#include "Others\MovingBlock.h"
#include "Others\SimpleObject.h"
#include "Others\Door.h"

#include "Effect.h"

#include "Item.h"

#include "Weapons\Dagger.h"
#include "Weapons\Axe.h"
#include "Weapons\Boomerang.h"
#include "Weapons\HolyWater.h"
#include "Weapons\Bone.h"
#include "Weapons\Fireball.h"

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
	std::unordered_map<int, Bullet*> bulletSpawners;

public:
	Spawner();

	static Spawner* GetInstance();

	void CreateObjectSpawner(int id);
	void CreateEffectSpawner(int id);
	void CreateItemSpawner(int id);
	void CreateBulletSpawner(int id);
	void CreateEnemySpawner(int id);

	LPGAMEOBJECT GetObjectSpawner(int id) { return objectSpawners[id]; }
	LPEFFECT GetEffectSpawner(int id) { return effectSpawners[id]; }
	LPITEM GetItemSpawner(int id) { return itemSpawners[id]; }
	Bullet* GetBulletSpawner(int id) { return bulletSpawners[id]; }
	LPENEMY GetEnemySpawner(int id) { return enemySpawners[id]; }

	LPGAMEOBJECT SpawnObject(int id, float x, float y, int item_id);
	LPEFFECT SpawnEffect(int id, float x, float y);
	LPITEM SpawnItem(int id, float x, float y);
	Bullet* SpawnBullet(int id, float x, float y, bool flip);
	LPENEMY SpawnEnemy(int id, float x, float y, float l, float r, bool flip);

};

