#pragma once

#include "GameObject.h"
#include "..\ID.h"
#include "Simon.h"
#include "Others\TitleBat.h"
#include "Others\TitleBG.h"
#include "Others\TitleText.h"
#include "Others\IntroBat.h"
#include "Others\IntroBG.h"
#include "Others\IntroCloud.h"
#include "Others\IntroSimon.h"

class Generator
{
public:
	static LPGAMEOBJECT PlayerCreate() { return new Simon; }
	static LPGAMEOBJECT ObjectCreate(int id);
	static LPGAMEOBJECT MapCreate(int id) { return 0; }
	static LPGAMEOBJECT EnemyCreate(int id) { return 0; }
};

