//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include <string>
#include <Springbok/Parsing/UTF8.h>
#include <Springbok/Generic/Logic.h>
#include <Springbok/Math/Operations.h>

template<typename T> std::string ToString(T x){ return std::to_string(x); };
inline std::string ToString(const std::string& x){ return x; };
// Works for float, int, etc.

inline std::string HumanString(float x)
{
	float absX = Abs(x);
	float roundTo = 100.f;
	if(absX > 1000.00)
		roundTo = 250.f;
	else if(absX > 100.00)
		roundTo = 5.0f;
	else if(absX > 10.00)
		roundTo = 1.0f;
	else if(absX > 2.00)
		roundTo = 0.5f;
	else if(absX > 1.00)
		roundTo = 0.25f;
	else if(absX > 0.25)
		roundTo = 0.125f;
	else
		roundTo = 0.025f;
	
	return ToString(Round(x, roundTo));
};