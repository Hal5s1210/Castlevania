#pragma once

#include <d3d9.h>

class Viewport
{
private:
	static Viewport* _instance;

	bool auto_move;
	bool switchview;

	float x, y;
	int width, height;

	float vx, vy;

	float dest_x, dest_y;
	bool reach_dest;

public:
	Viewport();

	static Viewport* GetInstance();

	void SetPosition(float x, float y) { this->x = x; this->y = y; }
	void SetSize(int w, int h) { width = w; height = h; }

	void GetPosition(float& x, float& y) { x = this->x; y = this->y; }
	void GetSize(int& w, int& h) { w = width; h = height; }

	void SetSwitchView(bool s) { switchview = s; }
	bool IsSwitchView() { return switchview; }

	void SetAuto(bool a) { auto_move = a; }
	bool IsAuto() { return auto_move; }

	void GoToX(float x);
	bool IsReachAutoDest() { return reach_dest; }

	void Update(DWORD dt);
};

