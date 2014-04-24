#include "Debug.h"
#include <iostream>

void Debug::Write(const char* message)
{
	std::cerr << message << std::endl;
}


