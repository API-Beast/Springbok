// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "Range.h"
#include <Springbok/Math/Operations.h>

template<typename T>
constexpr Range<T>::Range(T start, T end) : Start(Min(start, end)), End(Max(start, end))
{
}

template<typename T>
template<typename P>
constexpr Range<T>::Range(const Range<P>& other)
 : Start(other.Start), End(other.End) {}

template<typename T>
constexpr Range<T>::operator bool()
{
	return Start != End;
}

template<typename T>
constexpr Range<T> Range<T>::getIntersection(const Range<T>& other)
{
	return (Max(other.Start, Start) > Min(other.End, End)) ? Range<T>() : Range<T>(Max(other.Start, Start), Min(other.End, End));
}

template<typename T>
constexpr Range<T> Range<T>::getUnion(const Range<T>& other)
{
	return Range<T>(Min(other.Start, Start), Max(other.End, End));
}

template<typename T>
constexpr Range<T> Range<T>::getIntersection(const T& a, const T& b)
{
	return getIntersection(Range<T>(a, b));
}

template<typename T>
constexpr Range<T> Range<T>::getUnion(const T& a, const T& b)
{
	return getUnion(Range<T>(a, b));
}

template<typename T>
constexpr T Range<T>::bound(const T& val)
{
	return BoundBy(val, this->Start, this->End);
}

template<typename T>
constexpr T BoundBy(T value, Range<T> range)
{
	return (value < range.Start) ? range.Start : ((range.End < value) ? range.End : value);
};
