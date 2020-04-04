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
	default:
		break;
	}

	return obj;
}
