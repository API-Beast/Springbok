#pragma once

#include <iostream>

namespace Debug 
{
	void Write(const char* message);

	template<typename T, typename... Args> void Write(const char* message, T value, Args... args)
	{
		if(message[0] == '\0')
			return;
		
		while(*message) 
		{
			if(*message == '$') 
			{
				std::cerr << value;
				Write(message + 1, args...); 
				return;
			}
			else if(*message == '\0')
				std::cerr << std::endl;
			else
				std::cerr.put(*message++);
		}
		// More values given than dollars; Just give the beggar valuables.
		// Ehem, I mean, fallback to printing the remaining values as list
		std::cerr << "; " << value << std::endl;
	}
}
