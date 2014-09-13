// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "KeyframeList.h"
#include <algorithm>

template<typename T>
T KeyframeList<T>::operator[](float position) const
{
	if(Frames.empty())
		return T();
	
	if(Repeat)
	{
		float animStart = Frames.front().Time;
		float animStop  = Frames. back().Time;
		auto modulo = [](float a, float b){ return a - (b * int(a/b)); };
		if(position < animStart || position > animStop)
			position = animStart + modulo(position, animStop-animStart);
	}
	
	// This is a bit tricky
	// std::lower_bound returns the first item that is not smaller than b
	// We change the comparison to smaller than or equal to b
	// So the returned iterator is always bigger than b
	// Then we subtract 1 from the index so we get the value that is smaller or equal to b.
	auto compare = [](const Keyframe& a, float b){ return a.Time <= b; };
	auto it = std::lower_bound(Frames.begin(), Frames.end(), position, compare);
	int index = it - Frames.begin() - 1;
	
	if(index == -1)
		index = 0;
	
	// Linear interpolation
	Keyframe start = Frames[index];
	Keyframe end = start;
	if(index + 1 < Frames.size())
		end = Frames[index+1];
	
	if(!Cubic)
	{
		if(start.Time == end.Time)
				return start.Value;
		return InterpolateLinear(start.Value, end.Value, start.Time, end.Time, position);
	}
	// Cubic interpolation
	else
	{
		Keyframe prev = start;
		Keyframe next = start;
		
		if(index + 2 < Frames.size())
			next = Frames[index+2];
		if(index > 0)
			prev = Frames[index-1];
		
		if(start.Time == end.Time)
			return start.Value;
		
		return InterpolateCubic(prev.Value, start.Value, end.Value, next.Value, start.Time, end.Time, position);
	}
};

template<typename T>
void KeyframeList<T>::insert(float position, const T& value)
{
	auto compare = [](const Keyframe& a, float b){ return a.Time < b; };
	auto it      = std::lower_bound(Frames.begin(), Frames.end(), position, compare);
	Frames.insert(it, {position, value});
}