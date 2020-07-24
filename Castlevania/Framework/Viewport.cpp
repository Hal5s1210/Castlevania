#include "Viewport.h"

Viewport* Viewport::_instance = 0;

Viewport::Viewport()
{
	x = y = 0;
	vx = vy = 0;
	auto_move = false;
	switchview = false;
}

Viewport* Viewport::GetInstance()
{
	if (!_instance) _instance = new Viewport;
	return _instance;
}


void Viewport::GoToX(float dest_x)
{
	auto_move = true;
	reach_dest = false;
	vx = x == dest_x ? 0 : x < dest_x ? 0.067 : -0.067;
	this->dest_x = dest_x;
}

void Viewport::Update(DWORD dt)
{
	if (auto_move)
	{
		if (!reach_dest)
		{

			x += vx * dt;
			y += vy * dt;

			if ((vx > 0 && x >= dest_x) || (vx < 0 && x <= dest_x))
			{
				reach_dest = true;
				x = dest_x;
				vx = 0;
			}
		}
	}
}
