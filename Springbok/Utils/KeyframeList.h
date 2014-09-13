// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <vector>
#include "Functions.h"

template<typename T>
class KeyframeList
{
public:
	struct Keyframe{ float Time; T Value;  };
public:
	KeyframeList() = default;
	KeyframeList(const std::initializer_list<Keyframe>& list) : Frames(list){};
	KeyframeList(const T& value){ Frames.push_back({0.0f, value}); };
	
	T operator[](float position) const;
	void insert(float position, const T& value);
	void clear(){ Frames.clear(); };
public:
	std::vector<Keyframe> Frames;
	bool Cubic  = true;
	bool Repeat = false;
};

#include "KeyframeList_Templates.hpp"