// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

/** @ingroup Angle
 * The Radian class is a lightweight wrapper around the \a float datatype used by low level functions like \ref Sin and \ref Cos.
 * It's purpose is to denote the difference between a arbitary floating number and a \ref Radian so that classes like \ref Angle can convert accordingly.
*/
struct Radian
{
public:
	constexpr Radian(float value) : radians(value) {};
	Radian(){};
	operator float&(){ return radians; };
	constexpr operator const float&() const { return radians; };
private:
	float radians = 0.f;
};

//! A half turn in radians. Equal to the ratio of a circle's circumference to it's diameter.
constexpr Radian PI  = 3.14159;
//! A full turn in radians. Equal to the ratio of a circle's circumference to it's radius.
constexpr Radian Tau = PI * 2;