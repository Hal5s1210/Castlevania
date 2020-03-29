#include "Viewport.h"

Viewport* Viewport::_instance = 0;

Viewport::Viewport()
{
	x = y = 0;
}

Viewport* Viewport::GetInstance()
{
	if (!_instance) _instance = new Viewport;
	return _instance;
}