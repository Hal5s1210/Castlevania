#include "Candle.h"

void Candle::Update(DWORD dt)
{

}

void Candle::Render(float x, float y)
{
	currentAnimation.first->Draw(currentAnimation.second, this->x + x, this->y + y);
}

void Candle::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + 8;
	b = t + 16;
}