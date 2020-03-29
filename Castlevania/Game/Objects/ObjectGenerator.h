#pragma once

#include "GameObject.h"
#include "..\ID.h"
#include "Simon.h"
#include "TitleBat.h"
#include "TitleBG.h"
#include "TitleText.h"
#include "IntroBat.h"
#include "IntroBG.h"
#include "IntroCloud.h"
#include "IntroSimon.h"

class Generator
{
public:
	static LPGAMEOBJECT PlayerCreate() { return new Simon; }
	static LPGAMEOBJECT ObjectCreate(int id);
	static LPGAMEOBJECT MapCreate(int id) { return 0; }
	static LPGAMEOBJECT EnemyCreate(int id) { return 0; }
};

