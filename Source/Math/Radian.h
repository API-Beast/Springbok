// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

//! @ingroup Angle
//! @{
struct Radian
{
public:
	constexpr Radian(float value) : radians(value) {};
	Radian(){};
	operator float&(){ return radians; };
	constexpr operator const float&() const { return radians; };
private:
	float radians=0.f;
};
//! @}

extern const Radian PI;
extern const Radian Tau;