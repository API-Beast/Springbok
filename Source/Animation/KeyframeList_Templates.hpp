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
	auto node = NodePath.BaseNode;
	auto nextNode = node->Next;
	auto prevNode = node->Previous;
	auto nextNextNode = node;
	if(nextNode == nullptr)
		nextNode = node;
	else
		nextNextNode = nextNode->Next;
	if(prevNode == nullptr)
		prevNode = node;
	if(nextNextNode == nullptr)
		nextNextNode = node;
	
	auto prev     = prevNode->Data;
	auto start    = node->Data;
	auto end      = nextNode->Data;
	auto next     = nextNextNode->Data;
	return Interpolate(Parent->InterpolationMethod, prev.Value, start.Value, end.Value, next.Value, start.Key, end.Key, this->Index, *Parent->EasingFunction);
}

template<typename T>
void KeyframeList<T>::ReferencePoint::insert(const T& value)
{;
	if(!NodePath.hasFoundValue())
		NodePath.insert();
	NodePath.BaseNode->Data.Value = value;
}

template<typename T>
void KeyframeList<T>::ReferencePoint::remove()
{;
	if(NodePath.hasFoundValue())
		NodePath.remove();
}

template<typename T>
typename KeyframeList<T>::ReferencePoint KeyframeList<T>::operator[](float position)
{
	KeyframeList<T>::ReferencePoint retVal;
	retVal.NodePath = Keyframes.findNode(position);
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