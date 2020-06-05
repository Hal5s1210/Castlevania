#include "SubWeapon.h"
#include "..\..\Scenes\Scene.h"
#include "..\..\Board.h"
#include "..\Spawner.h"
#include "Stopwatch.h"

SubWeapon::SubWeapon(LPGAMEOBJECT wielder)
{
	this->wielder = wielder;
	delayTimeStart = -1;
	delayTime = 200;
	bulletcount = 0;
}

void SubWeapon::SetWeapon(int weapon, int shot, int heart) 
{
	current = weapon; 
	this->shot = shot; 
	this->heart = heart; 
}


bool SubWeapon::IsUsable()
{
	if (current == 5)
		return heart >= 5 ? !Stopwatch::IsTimePause() : false;

	return (current != 0 && bulletcount < shot && heart > 0);
}


void SubWeapon::Active()
{
	if (current == 5)
	{
		Stopwatch::TimeStop(shot);
		Board::GetInstance()->SubWeaponUsed(5);
		return;
	}

	if (weaponready) return;

	if (bulletcount < shot)
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
			int weapon_id = -1;

			switch (current)
			{
			case 1:	weapon_id = DAGGER_ID; break;
			case 2:	weapon_id = AXE_ID; break;
			case 3:	weapon_id = BOOMERANG_ID; break;
			case 4:	weapon_id = HOLYWATER_ID; break;

			default:
				break;
			}


			if (weapon_id != -1)
			{
				if (GetTickCount() - delayTimeStart >= delayTime)
				{
					Bullet* b = Spawner::GetInstance()->SpawnBullet(weapon_id, x, y, flip);
					b->SetShooter(wielder);

					Scenes::GetInstance()->GetScene()->AddBullet(b);
					bulletcount++;

					weaponready = false;
					Board::GetInstance()->SubWeaponUsed(1);
				}
			}

		}
	}
}