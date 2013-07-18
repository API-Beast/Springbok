// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <Springbok/Generic/Structures/SkipList.h>
#include <Springbok/Generic/Structures/Associative.h>
#include "Interpolation.h"

template<typename T>
class KeyframeList
{
public:
	class ReferencePoint
	{
	public:
		void insert(const T& value);
		void remove();
		operator T() const;

		float Index;
		SkipListNode< Associative<float, T> >* Node;
		KeyframeList* Parent;
	};
public:
	~KeyframeList();
	template<typename E>
	void setInterpolationMethod(Interpolation interpolation, const E& easingFunction);
	ReferencePoint operator[](float position);
private:
	Interpolation InterpolationMethod = Interpolation::Linear;
	EasingFunctionBase* EasingFunction = nullptr;
	SkipList< Associative<float, T> > Keyframes;
	friend ReferencePoint;
};

#include "KeyframeList_Templates.hpp"