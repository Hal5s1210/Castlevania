#pragma once

#include "..\..\Framework\GameObject.h"
#include "Simon.h"
#include "IntroBat.h"
#include "IntroBG.h"
#include "IntroCloud.h"
#include "TitleBat.h"
#include "TitleBG.h"
#include "TitleText.h"

class ObjectGenerator : public Generator
{
	static Generator* _instance;
public:
	static Generator* GetInstance();

	LPGAMEOBJECT ObjectCreate(int id) { return 0; }
	LPGAMEOBJECT MapCreate(int id) { return 0; }
	LPGAMEOBJECT EnemyCreate(int id) { return 0; }
};

