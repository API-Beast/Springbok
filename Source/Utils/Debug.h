#pragma once

#include <iostream>

namespace Debug 
{
	void Write(const char* message);

	template<typename T, typename... Args> void Write(const char* message, T value, Args... args)
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
					std::cout << value;
					char next = (message + 1)[0];
					if (next == '\0')
						std::cout << std::endl;
 					else Write(message + 1, args...); 
					return;
				}
			}
			std::cout << *message++;
		}
		std::cout << "\nWARNING: extra arguments provided to Debug::Write()" << std::endl;
	}
}
