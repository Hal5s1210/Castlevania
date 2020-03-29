#pragma once

class Viewport
{
private:
	static Viewport* _instance;
	float x, y;
	int width, height;

public:
	Viewport();

	static Viewport* GetInstance();

	void SetPosition(float x, float y) { this->x = x; this->y = y; }
	void SetSize(int w, int h) { width = w; height = h; }
	void GetPosition(float& x, float& y) { x = this->x; y = this->y; }
	void GetSize(int& w, int& h) { w = width; h = height; }

};

