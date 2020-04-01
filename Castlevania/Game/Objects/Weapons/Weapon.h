#pragma once

#include "..\..\ID.h"
#include "..\GameObject.h"

class Weapon : public GameObject
{
protected:
	int index;

public:
	virtual void SetFrameIndex(int i) { index = i; }
	void Render(float x = 0, float y = 0) {}
	virtual void Render(float x = 0, float y = 0, bool flip = false) = 0;
};



class NoWeapon : public Weapon
{
public:
	NoWeapon();
	void Render(float x = 0, float y = 0, bool flip = false);
	void GetBoundingBox(float& l, float& t, float& r, float& b);

};

