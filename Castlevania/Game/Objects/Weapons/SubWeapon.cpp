#include "SubWeapon.h"
#include "..\..\Scenes\Scene.h"

SubWeapon::SubWeapon()
{
	delayTimeStart = -1;
	delayTime = 200;

	dagger = new Dagger;
	axe = new Axe;
	boomerang = new Boomerang;
	holywater = new HolyWater;
	stopwatch = new Stopwatch;
}

bool SubWeapon::IsUsable()
{
	return (current != 0 && weapons.size() < shot);
}


void SubWeapon::Active()
{
	if (weaponready) return;

	ready_weapon = NULL;

	if (weapons.size() < shot)
	{
		weaponready = true;
		
		delayTimeStart = GetTickCount();

		switch (current)
		{
		case 1:	ready_weapon = dagger->Clone();	break;
		case 2:	ready_weapon = axe->Clone(); break;
		case 3:	ready_weapon = boomerang->Clone(); break;
		case 4: ready_weapon = holywater->Clone(); break;

		default:
			break;
		}
	}
}
void SubWeapon::AddWeapon(bool flip, float x, float y)
{
	if (weaponready)
	{
		if (ready_weapon != NULL)
		{
			if (GetTickCount() - delayTimeStart >= delayTime)
			{
				dynamic_cast<Weapon*>(ready_weapon)->Ready(x, y, flip);

				weapons.push_back(dynamic_cast<Weapon*>(ready_weapon));
				ready_weapon = NULL;
				weaponready = false;
			}
		}
	}
}


void SubWeapon::Update(DWORD dt, std::vector<LPGAMEOBJECT>* objects)
{
	for (int i = 0; i < weapons.size(); i++)
	{
		weapons[i]->Update(dt, objects);

		if (weapons[i]->IsHitSomething() || weapons[i]->IsOutOfView())
		{
			delete weapons[i];
			weapons.erase(weapons.begin() + i);
			--i;
		}
	}
}

void SubWeapon::Render(float x, float y)
{
	for (LPGAMEOBJECT o : weapons)
	{
		o->Render(x, y);
	}
}