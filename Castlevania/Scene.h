#pragma once

#define TITLE_SCENE_ID			0
#define INTRO_SCENE_ID			1


#include <vector>
#include "Game.h"
#include "GameObject.h"

class Scene
{
protected:
	bool sceneStart;
	bool sceneEnd;
	int id;

	LPKEYEVENTHANDLER keyHandler;

	std::vector<LPGAMEOBJECT> mapObjs;
	std::vector<LPGAMEOBJECT> items;
	std::vector<LPGAMEOBJECT> enemies;

public:
	bool IsStarted() { return sceneStart; }
	bool IsEnd() { return sceneEnd; }
	int GetId() { return id; }

	virtual LPKEYEVENTHANDLER GetKeyHandler() { return keyHandler; }

	virtual void LoadScene() = 0;
	virtual void EndScene() = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;

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

	void LoadResource();
	void Update(DWORD dt);
	void Render();

	LPKEYEVENTHANDLER GetKeyHandler() { return scenes[currentScene]->GetKeyHandler(); }
	LPSCENE CurrentScene() { return scenes[currentScene]; }
	void NextScene() { currentScene++; }

};

