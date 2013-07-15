// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <Springbok/Generic/Structures/SkipList.h>
#include <Springbok/Generic/Structures/Associative.h>

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
		SkipList< Associative<float, T> >* List;
	};
public:
	ReferencePoint operator[](float position);
private:
	SkipList< Associative<float, T> > Keyframes;
};

#include "KeyframeList_Templates.hpp"