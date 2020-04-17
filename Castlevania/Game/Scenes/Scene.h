#pragma once

#define TITLE_SCENE_ID			0
#define INTRO_SCENE_ID			1


#include <vector>

#include "..\..\Framework\Input.h"
#include "..\..\Framework\Sound.h"
#include "..\..\Framework\Debug.h"
#include "..\..\Framework\Viewport.h"
#include "..\Parser.h"
#include "..\Objects\Spawner.h"
#include "..\Map\TileMap.h"
#include "..\Map\Grid.h"
#include "..\Board.h"
#include "..\..\Dependencies\pugixml\src\pugixml.hpp"


class Scene
{
protected:
	float x, y;
	bool loaded;
	LPCWSTR filePath;

	LPKEYEVENTHANDLER keyhandler;

	Grid* grid;
	Tilemap* tilemap;

	Board* board;
	Simon* player;
	
	std::vector<LPGAMEOBJECT> objects;
	std::vector<LPEFFECT> effects;
	std::vector<LPITEM> items;

	void LoadFromFile();

public:
	Scene(float x, float y, LPCWSTR filepath) :x(x), y(y) { filePath = filepath; }
	
	bool IsLoaded() { return loaded; }

	LPKEYEVENTHANDLER GetKeyHandler() { return keyhandler; }
	Simon* GetPlayer() { return player; }

	void AddEffect(LPEFFECT effect) { effects.push_back(effect); }
	void AddItem(LPITEM item) { items.push_back(item); }

	void NextArea(int i) { tilemap->SetArea(i); }

	virtual void Load();
	virtual void Unload();
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;

};
typedef Scene* LPSCENE;


class Scenes
{
private:
	static Scenes* _instance;
	std::unordered_map<int, LPSCENE> scenes;
	int currentID;
	int switchScene = -1;

public:
	static Scenes* GetInstance();

	void Add(int id, LPSCENE scene);
	LPSCENE GetScene() { return scenes[currentID]; }
	void NextScene(int id);
	void SwitchScene();

};

