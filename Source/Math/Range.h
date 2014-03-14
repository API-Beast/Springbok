// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

//~ struct Range
//~ A range is a one dimensional line.
template<typename T>
struct Range
{
	//~ Member variables
	T MinVal = T(); // The smaller of the two points.
	T MaxVal = T(); // The bigger of the two points.
	
	//~ Constructors
	constexpr Range(){};
	constexpr Range(T val) : MinVal(val), MaxVal(val){};
	constexpr Range(T start, T end);
	template<typename P>
	constexpr Range(const Range<P>& other);
	
	//~ Operators
	constexpr explicit operator bool() const; // Returns `true` if Start is not equal to End.
	constexpr Range<T> operator+(const T offset); // Shift both values by offset
	constexpr Range<T> operator-(const T offset);
	
	//~ Methods
	constexpr Range<T> intersect(const Range<T>& other) const;
	constexpr Range<T> intersect(const T& a, const T& b) const;
	constexpr Range<T> unite(const Range<T>& other) const;
	constexpr Range<T> unite(const T& a, const T& b) const;
	
	constexpr T bound(const T& value);
};

//~ Typedefs
using RangeF = Range<float>;
using RangeI = Range<int>;
using RangeU = Range<unsigned>;
//~!

#include <ostream>

template<typename T>
std::ostream& operator<< (std::ostream& stream, const Range<T>& obj)
{
	return stream << "[" << obj.MinVal << "," << obj.MaxVal << "]";
}

#include "Range_Templates.hpp"