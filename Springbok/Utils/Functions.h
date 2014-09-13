//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

template<typename T, typename... Args>
void DebugLog(const char* message, T value, Args... args);
void DebugLog(const char* message);

template<typename T, typename D>
T Approach(T from, T to, D limit);

#define templ  template<class T>
#define templc template<class T> constexpr

templ T InterpolateLinear(T start, T end, float factor);
templ T InterpolateLinear(T start, T end, float startT, float endT, float time);

templ T InterpolateCubic (T prev,  T start, T end, T after, float factor);
templ T InterpolateCubic (T prev,  T start, T end, T after, float startT, float endT, float time);

templc T Min(T a, T b);
templc T Max(T a, T b);
templc T BoundBy(T lowerBound, T value, T upperBound);
templc T Abs(const T val);

#undef templ
#undef templc

#include "Functions_Templates.hpp"