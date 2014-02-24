#include "Debug.h"
#include <iostream>

void Debug::Write(const char* message)
{
	if (message == "" || message[0] == '\0')
		return;
	while (*message) 
	{
		if (*message == '$') 
		{
			if (*(message + 1) == '$') 
			{
				++message;
			}
			else 
			{
				std::cout << "\nWARNING: invalid format string: missing arguments" << std::endl;
				return;
			}
		}
		std::cout << *message++;
	}
	std::cout << "\n";
}


