// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "KeyframeList.h"
#include "Interpolation.h"
#include <algorithm>

template<typename T>
T KeyframeList<T>::operator[](float position) const
{
	if(RepeatAnimation)
		if(position < FirstKeyFrame || position > LastKeyFrame)
			position = FirstKeyFrame + Modulo(position, LastKeyFrame-FirstKeyFrame);
	
	// This is a bit tricky
	// std::lower_bound returns the first item that is not smaller than b
	// We change the comparison to smaller than or equal to b
	// So the returned iterator is always bigger than b
	// Then we subtract 1 from the index so we get the value that is smaller or equal to b.
	auto compare = [](const Keyframe& a, float b){ return a.Time <= b; };
	auto it = std::lower_bound(Keyframes.begin(), Keyframes.end(), position, compare);
	int index = it - Keyframes.begin() - 1;
	
	if(index == -1)
		index = 0;
	
	if(Keyframes.empty())
		return T();
	
	// For linear interpolation
	Keyframe start = Keyframes[index];
	Keyframe end = start;
	
	// For cubic interpolation
	Keyframe prev = start;
	Keyframe next = start;
	
	if(index + 1 < Keyframes.size())
		end = Keyframes[index+1];
	if(index + 2 < Keyframes.size())
		next = Keyframes[index+2];
	if(index > 0)
		prev = Keyframes[index-1];
	
	if(start.Time == end.Time)
		return start.Value;
	
	return Interpolate(InterpolationMethod, prev.Value, start.Value, end.Value, next.Value, start.Time, end.Time, position, *EasingFunction);
};

template<typename T>
void KeyframeList<T>::insert(float position, const T& value)
{
	auto compare = [](const Keyframe& a, float b){ return a.Time < b; };
	auto it = std::lower_bound(Keyframes.begin(), Keyframes.end(), position, compare);
	
	Keyframes.insert(it, {position, value});
	if(position < FirstKeyFrame)
		FirstKeyFrame = position;
	if(position > LastKeyFrame)
		LastKeyFrame = position;
}

template<typename T>
template<typename E>
void KeyframeList<T>::setInterpolationMethod(Interpolation interpolation, const E& easingFunction)
{
	InterpolationMethod = interpolation;
	EasingFunction = new E(easingFunction);
}

template<typename T>
void KeyframeList<T>::setInterpolationMethod(Interpolation interpolation)
{
	InterpolationMethod = interpolation;
}

template<typename T>
KeyframeList<T>::~KeyframeList()
{
	delete EasingFunction;
}