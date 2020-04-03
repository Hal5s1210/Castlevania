#include "Generator.h"

LPGAMEOBJECT Generator::PlayerCreate()
{
	Simon* simon = new Simon;
	simon->Init(SIMON_PATH);
	simon->SetAnimation(0);

	return simon;
}

LPGAMEOBJECT Generator::ObjectCreate(int id)
{
	LPGAMEOBJECT obj = 0;

	switch (id)
	{
	case TITLEBG_ID:
		obj = new SimpleObject;
		obj->Init(TITLEBG_PATH);
		obj->SetAnimation(0);
		break;

	case TITLEBAT_ID:
		obj = new SimpleObject;
		obj->Init(TITLEBAT_PATH);
		obj->SetAnimation(0);
		break;

	case TITLETEXT_ID:
		obj = new SimpleObject;
		obj->Init(TITLETEXT_PATH);
		obj->SetAnimation(0);
		break;

	case INTROBG_ID:
		obj = new SimpleObject;
		obj->Init(INTROBG_PATH);
		obj->SetAnimation(0);
		break;

	case INTROBAT_ID:
		obj = new SimpleObject;
		obj->Init(INTROBAT_PATH);
		obj->SetAnimation(0);
		break;

	case INTROCLOUD_ID:
		obj = new SimpleObject;
		obj->Init(INTROCLOUD_PATH);
		obj->SetAnimation(0);
		break;

	case INTROSIMON_ID:
		obj = new SimpleObject;
		obj->Init(INTROSIMON_PATH);
		obj->SetAnimation(0);
		break;

	default:
		break;
	}

	return obj;
}
