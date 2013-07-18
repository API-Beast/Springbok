// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "KeyframeList.h"
#include "Interpolation.h"

template<typename T>
KeyframeList<T>::ReferencePoint::operator T() const
{
	auto nextNode = Node->Next;
	auto prevNode = Node->Previous;
	auto nextNextNode = Node;
	if(nextNode == nullptr)
		nextNode = Node;
	else
		nextNextNode = nextNode->Next;
	if(prevNode == nullptr)
		prevNode = Node;
	if(nextNextNode == nullptr)
		nextNextNode = Node;
	
	auto prev     = prevNode->Data;
	auto start    = Node->Data;
	auto end      = nextNode->Data;
	auto next     = nextNextNode->Data;
	return Interpolate(Parent->InterpolationMethod, prev.Value, start.Value, end.Value, next.Value, start.Key, end.Key, this->Index, *Parent->EasingFunction);
}

template<typename T>
void KeyframeList<T>::ReferencePoint::insert(const T& value)
{
	if(Node)
	{
		if(Node->Data.Key == Index)
		{
			Node->Data.Value = value;
			return;
		}
	}
	Parent->Keyframes.insert(Associative<float, T>(Index, value));
	// TODO: Save iteration and don't do the whole thing again for inseration
}

template<typename T>
typename KeyframeList<T>::ReferencePoint KeyframeList<T>::operator[](float position)
{
	KeyframeList<T>::ReferencePoint retVal;
	retVal.Node = Keyframes.find(position);
	retVal.Index = position;
	retVal.Parent = this;
	return retVal;
}

template<typename T>
template<typename E>
void KeyframeList<T>::setInterpolationMethod(Interpolation interpolation, const E& easingFunction)
{
	InterpolationMethod = interpolation;
	EasingFunction = new E(easingFunction);
}

template<typename T>
KeyframeList<T>::~KeyframeList()
{
	delete EasingFunction;
}