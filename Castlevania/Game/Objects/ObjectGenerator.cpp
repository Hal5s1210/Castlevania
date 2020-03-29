#include "ObjectGenerator.h"

LPGAMEOBJECT Generator::ObjectCreate(int id)
{
	switch (id)
	{
	case TITLEBG_ID:
		return new TitleBG;

	case TITLEBAT_ID:
		return new TitleBat;

	case TITLETEXT_ID:
		return new TitleText;

	case INTROBG_ID:
		return new IntroBG;

	case INTROBAT_ID:
		return new IntroBat;

	case INTROCLOUD_ID:
		return new IntroCloud;

	case INTROSIMON_ID:
		return new IntroSimon;

	default:
		return NULL;
		break;
	}
}
