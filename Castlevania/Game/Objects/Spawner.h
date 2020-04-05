#pragma once

#include <unordered_map>
#include "..\ID.h"
#include "GameObject.h"
#include "Simon.h"
#include "Others\Block.h"
#include "Others\Torch.h"
#include "Others\Candle.h"

class Spawner
{
private:
	static Spawner* _instance;
	std::unordered_map<int, LPGAMEOBJECT> spawners;

public:
	static Spawner* GetInstance();

	void CreateObjectSpawner(int id, pugi::xml_node root);
	LPGAMEOBJECT SpawnObject(int id);
};

