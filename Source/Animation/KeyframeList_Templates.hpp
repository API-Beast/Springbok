// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "KeyframeList.h"
#include "Interpolation.h"

template<typename T>
T KeyframeList<T>::operator[](float position) const
{
	int index = Keyframes.findIndex(position);
	
	if(index == -1)
		index = 0;
	
	if(Keyframes.empty())
		return T();
	
	// For linear interpolation
	Keyframe start = Keyframes.Data[index];
	Keyframe end = start;
	
	// For cubic interpolation
	Keyframe prev = start;
	Keyframe next = start;
	
	if(index + 1 < Keyframes.Data.UsedLength)
		end = Keyframes.Data[index+1];
	if(index + 2 < Keyframes.Data.UsedLength)
		next = Keyframes.Data[index+2];
	if(index > 0)
		prev = Keyframes.Data[index-1];
	
	if(start.Time == end.Time)
		return start.Value;
	
	return Interpolate(InterpolationMethod, prev.Value, start.Value, end.Value, next.Value, start.Time, end.Time, position, *EasingFunction);
};

template<typename T>
void KeyframeList<T>::insert(float position, const T& value)
{
	Keyframes.insert({position, value});
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