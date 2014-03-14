// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "Range.h"
#include <Springbok/Math/Operations.h>

template<typename T>
constexpr Range<T>::Range(T start, T end) : MinVal(Min(start, end)), MaxVal(Max(start, end))
{
}

template<typename T>
template<typename P>
constexpr Range<T>::Range(const Range<P>& other)
 : MinVal(other.MinVal), MaxVal(other.MaxVal) {}

template<typename T>
constexpr Range<T>::operator bool()
{
	return MinVal < MaxVal;
}

template<typename T>
constexpr Range<T> Range<T>::intersect(const Range<T>& other)
{
	return (Max(other.MinVal, MinVal) > Min(other.MaxVal, MaxVal)) ? Range<T>() : Range<T>(Max(other.MinVal, MinVal), Min(other.MaxVal, MaxVal));
}

template<typename T>
constexpr Range<T> Range<T>::unite(const Range<T>& other)
{
	return Range<T>(Min(other.MinVal, MinVal), Max(other.MaxVal, MaxVal));
}

template<typename T>
constexpr Range<T> Range<T>::intersect(const T& a, const T& b)
{
	return intersect(Range<T>(a, b));
}

template<typename T>
constexpr Range<T> Range<T>::unite(const T& a, const T& b)
{
	return unite(Range<T>(a, b));
}

template<typename T>
constexpr T Range<T>::bound(const T& val)
{
	return BoundBy(val, this->MinVal, this->MaxVal);
}

template<typename T>
constexpr T BoundBy(T value, Range<T> range)
{
	return (value < range.MinVal) ? range.MinVal : ((range.MaxVal < value) ? range.MaxVal : value);
};
