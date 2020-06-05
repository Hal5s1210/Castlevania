#include "Stopwatch.h"
#include "..\..\Scenes\Scene.h"

DWORD Stopwatch::timestop = 3000;
DWORD Stopwatch::stoptimestart = -1;
bool Stopwatch::pause = false;
bool Stopwatch::timeout = true;

void Stopwatch::TimeStop(int level)
{
	pause = true;
	timestop = 3000 + level * 1000;
	std::vector<LPENEMY> enemies;
	enemies = *Scenes::GetInstance()->GetScene()->GetEnemyList();
	for (LPENEMY e : enemies)
	{
		e->PauseAnimation();
	}

	stoptimestart = GetTickCount();
	timeout = false;
}

void Stopwatch::TimeResume()
{
	pause = false;
	std::vector<LPENEMY> enemies;
	enemies = *Scenes::GetInstance()->GetScene()->GetEnemyList();
	for (LPENEMY e : enemies)
	{
		e->PlayAnimtion();
	}
}

void Stopwatch::Update(DWORD dt)
{
	if (GetTickCount() - stoptimestart > timestop)
	{
		timeout = true;
	}
}
