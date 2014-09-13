//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "Functions.h"
#include <iostream>

template<typename T, typename... Args> void DebugLog(const char* message, T value, Args... args)
{
	if(message[0] == '\0')
		return;
	
	while(*message) 
	{
		if(*message == '$') 
		{
			std::cerr << value;
			DebugLog(message + 1, args...); 
			return;
		}
		else if(*message == '\0')
			std::cerr << std::endl;
		else
			std::cerr.put(*message++);
	}
	// More values...
	std::cerr << "; " << value << std::endl;
} 
 
template<typename T>
constexpr T Min(T a, T b)
{
	return (a < b) ? a : b;
};

template<typename T>
constexpr T Max(T a, T b)
{
	return (a < b) ? b : a;
};

template<typename T>
constexpr T BoundBy(T lowerBound, T value, T upperBound)
{
	return (value < lowerBound) ? lowerBound : ((upperBound < value) ? upperBound : value);
};

template<typename T>
constexpr T Abs(const T val)
{
	return (val > T()) ? val : -val;
}
 
template<typename T, typename D>
T Approach(T from, T to, D limit)
{
	D diff = Abs((from - to));
	limit = Min<D>(diff, limit);
	if(diff > limit)
	{
		if(from < to)
			return from + limit;
		else
			return from - limit;
	}
	else
		return to;
};

template<typename T>
T InterpolateLinear(T start, T end, float factor)
{
	return start + (end - start) * factor;
};

template<typename T>
T InterpolateCubic(T prev, T start, T end, T after, float factor)
{
	// Don't ask me for proper names for these variables or the logic behind them, this is math.
	// And I have no idea about math.
	T a0, a1, a2;
	a0 = after - end - prev + start;
	a1 = prev - start - a0;
	a2 = end - prev;
	return start + (a0 * factor*factor*factor) + (a1 * factor*factor) + (a2 * factor);
};

template<typename T>
T InterpolateLinear(T start, T end, float startT, float endT, float time)
{
	return InterpolateLinear(start, end, (time-startT)/(endT-startT));
};

template<typename T>
T InterpolateCubic (T prev,  T start, T end, T after, float startT, float endT, float time)
{
	return InterpolateCubic(prev, start, end, after, (time-startT)/(endT-startT));
};