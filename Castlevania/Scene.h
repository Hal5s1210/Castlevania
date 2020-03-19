#pragma once

#define TITLE_SCENE_ID			0
#define TITLE_SCENE_TEX_ID		1000
#define TITLE_SCENE_DIR			L"Resources\\Textures\\NES - Castlevania - Title Screen.png"

#define INTRO_SCENE_ID			1
#define INTRO_SCENE_TEX_ID		2000
#define INTRO_SCENE_DIR			L"Resources\\Textures\\NES - Castlevania - Cutscenes & Credits.png"


#include <vector>
#include "GameObject.h"
#include "Game.h"

class Scene
{
protected:
	bool sceneStart;
	bool sceneEnd;
	int id;
	std::vector<LPGAMEOBJECT> mapObj;
	std::vector<LPGAMEOBJECT> items;
	std::vector<LPGAMEOBJECT> enemies;

public:
	bool IsStarted() { return sceneStart; }
	bool IsEnd() { return sceneEnd; }
	int GetId() { return id; }

	virtual void LoadScene() = 0;
	virtual void EndScene() = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;

	virtual void ButtonDown(int keyCode) = 0;
	virtual void ButtonUp(int keyCode) = 0;

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

	LPSCENE CurrentScene() { return scenes[currentScene]; }
	void NextScene() { currentScene++; }

};

