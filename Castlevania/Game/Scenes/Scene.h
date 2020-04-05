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
#include "..\..\Dependencies\pugixml\src\pugixml.hpp"


class Scene : public IKeyEventHandler
{
protected:
	float x, y;
	LPCWSTR filePath;
	
	Simon* player;

	Grid* grid;
	Tilemap* tilemap;

	std::vector<LPGAMEOBJECT> objects;

	void LoadFromFile();

public:
	Scene(LPCWSTR filepath) { filePath = filepath; }

	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;

};
typedef Scene* LPSCENE;


class Scenes
{
private:
	static Scenes* _instance;
	std::unordered_map<int, LPSCENE> scenes;
	int currentScene;

public:
	static Scenes* GetInstance();

	void Add(int id, LPSCENE scene);
	LPSCENE GetScene() { return scenes[currentScene]; }
	void NextScene(int id);

};

