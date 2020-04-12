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

	void LoadFromFile();

public:
	Scene(int x, int y, LPCWSTR filepath) :x(x), y(y) { filePath = filepath; }
	
	bool IsLoaded() { return loaded; }

	LPKEYEVENTHANDLER GetKeyHandler() { return keyhandler; }
	Simon* GetPlayer() { return player; }

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

public:
	static Scenes* GetInstance();

	void Add(int id, LPSCENE scene);
	LPSCENE GetScene() { return scenes[currentID]; }
	void NextScene(int id);

};

