#include "ObjectGenerator.h"

Generator* ObjectGenerator::_instance = 0;

Generator* ObjectGenerator::GetInstance()
{
	if (!_instance) _instance = new ObjectGenerator;
	return _instance;
}
