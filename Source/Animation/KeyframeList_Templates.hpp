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
	if(nextNode == nullptr)
		nextNode = Node;
	
	auto start    = Node->Data;
	auto end      = nextNode->Data; 
	return InterpolateLinear(start.Value, end.Value, start.Key, end.Key, this->Index);
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
	List->insert(Associative<float, T>(Index, value));
	// TODO: Save iteration and don't do the whole thing again for inseration
}

template<typename T>
typename KeyframeList<T>::ReferencePoint KeyframeList<T>::operator[](float position)
{
	KeyframeList<T>::ReferencePoint retVal;
	retVal.Node = Keyframes.find(position);
	retVal.Index = position;
	retVal.List = &Keyframes;
	return retVal;
}