// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

/** A range is a one dimensional line. */
template<typename T>
struct Range
{
	constexpr Range(){};
	constexpr Range(T start, T end);
	template<typename P>
	constexpr Range(const Range<P>& other);
	
	/** Returns \c true if Start is not equal to End. */
	constexpr operator bool() const;
	
	/** Gets the intersection between \c this and \a other.
	 * Example:
	 * ~~~
	 * RangeF a(-0.4f, 0.7f);
	 * RangeF result = a.getIntersection(0.0f, 1.0f);
	 * // Result == (0.0f, 0.7f)
	 * ~~~
	 */
	constexpr Range<T> getIntersection(const Range<T>& other) const;
	constexpr Range<T> getIntersection(const T& a, const T& b) const;
	constexpr Range<T> getUnion(const Range<T>& other) const;
	constexpr Range<T> getUnion(const T& a, const T& b) const;
	
	/** Returns \a value bound by \c this. */
	constexpr T bound(const T& value);
	
	float Start = 0.f; /**< The smaller of the two points. */
	float End   = 0.f; /**< The bigger of the two points. */ 
};
using RangeF = Range<float>;
using RangeI = Range<int>;
using RangeU = Range<unsigned>;

#include "Range_Templates.hpp"