// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

/** A range is a one dimensional line. */
template<typename T>
struct Range
{
	Range(T start, T end);
	/** Returns \c true if Start is not equal to End. */
	operator bool() const;
	Range<T> getIntersection(const Range<T>& other) const;
	Range<T> getUnion(const Range<T>& other) const;
	float Start=0.f;
	float End=0.f;
};
using RangeF = Range<float>;
using RangeI = Range<int>;
using RangeU = Range<unsigned>;