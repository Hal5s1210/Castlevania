#pragma once

#define TITLE_SCENE_ID			0
#define INTRO_SCENE_ID			1


#include <vector>

#include "..\..\Framework\Input.h"
#include "..\..\Framework\Sound.h"
#include "..\..\Framework\Debug.h"
#include "..\Objects\ObjectGenerator.h"
#include "..\Map\Map.h"
#include "..\..\Dependencies\pugixml\src\pugixml.hpp"


class Scene : public IKeyEventHandler
{
protected:
	bool sceneStart;
	bool sceneEnd;
	int id;
	float x, y;

	LPKEYEVENTHANDLER keyHandler;
	
	Map* map;

	LPGAMEOBJECT player;
	std::vector<LPGAMEOBJECT> mapObjs;
	std::vector<LPGAMEOBJECT> items;
	std::vector<LPGAMEOBJECT> enemies;

	void LoadFromFile(const wchar_t* filepath);

public:
	bool IsStarted() { return sceneStart; }
	bool IsEnd() { return sceneEnd; }
	int GetId() { return id; }

	LPKEYEVENTHANDLER GetKeyHandler() { return keyHandler; }
	void GetPosition(float& x, float& y) { x = this->x; y = this->y; }

	virtual void LoadScene() = 0;
	virtual void UpdateScene(DWORD dt) = 0;
	virtual void EndScene() = 0;
	virtual void RenderScene() = 0;

	virtual void Update(DWORD dt);
	virtual void Render();

};
typedef Scene* LPSCENE;


class Scenes
{
private:
	static Scenes* _instance;
	std::vector<LPSCENE> scenes;
	int currentScene;

public:
	static Scenes* GetInstance();

	void Add(LPSCENE scene);
	LPSCENE GetScene() { return scenes[currentScene]; }
	LPKEYEVENTHANDLER GetKeyHandler() { return scenes[currentScene]->GetKeyHandler(); }
	void NextScene() { if (currentScene < scenes.size())currentScene++; }

};

