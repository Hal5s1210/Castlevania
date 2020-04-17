#include "SubWeapon.h"
#include "..\..\Scenes\Scene.h"
#include "..\..\Board.h"

SubWeapon::SubWeapon(LPGAMEOBJECT wielder)
{
	this->wielder = wielder;
	delayTimeStart = -1;
	delayTime = 200;

	dagger = new Dagger(wielder);
	axe = new Axe(wielder);
	boomerang = new Boomerang(wielder);
	holywater = new HolyWater(wielder);
	stopwatch = new Stopwatch(wielder);
}

bool SubWeapon::IsUsable()
{
	return (current != 0 && weapons.size() < shot && heart > 0);
}


void SubWeapon::Active()
{
	if (weaponready) return;

	if (weapons.size() < shot)
	{
		weaponready = true;
		delayTimeStart = GetTickCount();
	}
}
void SubWeapon::AddWeapon(bool flip, float x, float y)
{
	if (weaponready)
	{
		if (current != 0)
		{
			LPGAMEOBJECT ready_weapon = NULL;

			switch (current)
			{
			case 1:	ready_weapon = dagger->Clone();	break;
			case 2:	ready_weapon = axe->Clone(); break;
			case 3:	ready_weapon = boomerang->Clone(); break;
			case 4: ready_weapon = holywater->Clone(); break;

			default:
				break;
			}

			if (ready_weapon)
			{
				if (GetTickCount() - delayTimeStart >= delayTime)
				{
					dynamic_cast<Weapon*>(ready_weapon)->Ready(x, y, flip);

					weapons.push_back(dynamic_cast<Weapon*>(ready_weapon));
					ready_weapon = NULL;
					weaponready = false;
					Board::GetInstance()->SubWeaponUsed(1);
				}
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