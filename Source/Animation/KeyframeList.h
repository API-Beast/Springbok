// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <Springbok/Containers/List.h>
#include "Interpolation.h"

template<typename T>
class KeyframeList
{
public:
	struct Keyframe{ float Time; T Value;  };
public:
	KeyframeList() = default;
	KeyframeList(const std::initializer_list<Keyframe>& list) : Keyframes(list){};
	KeyframeList(const T& value){ Keyframes.insert({0.0f, value}); };
	~KeyframeList();
	template<typename E>
	void setInterpolationMethod(Interpolation interpolation, const E& easingFunction);
	void setInterpolationMethod(Interpolation interpolation);
	T operator[](float position) const;
	void insert(float position, const T& value);
	void clear(){ Keyframes.clear(); };
private:
	Interpolation InterpolationMethod = Interpolation::Cubic;
	EasingFunctionBase* EasingFunction = nullptr;
	Map<Keyframe, float, &Keyframe::Time> Keyframes;
};

#include "KeyframeList_Templates.hpp"