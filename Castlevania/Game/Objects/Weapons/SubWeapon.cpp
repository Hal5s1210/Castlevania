#include "SubWeapon.h"
#include "..\..\Scenes\Scene.h"

SubWeapon::SubWeapon()
{
	dagger = new Dagger;
}


void SubWeapon::Active(bool flip, float x, float y)
{
	if (weapons.size() < shot)
	{
		switch (current)
		{
		case 1:
		{
			LPGAMEOBJECT d = dagger->Clone();
			d->SetFlip(!flip);
			if (flip)
			{
				d->SetPosition(x, y);
				d->SetSpeed(0.2, 0);
			}
			else
			{
				d->SetPosition(x - 16, y);
				d->SetSpeed(-0.2, 0);
			}
			weapons.push_back(dynamic_cast<Weapon*>(d));
		}
		break;

		default:
			break;
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