//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "Angle.h"

constexpr Angle Angle::FromDegree(float degree)
{
	return Angle(degree * Tau / 360);
}

constexpr Angle Angle::FromRadians(float radians)
{
	return Angle(radians);
}

constexpr Angle Angle::FromTurn(float turns)
{
	return Angle(turns * Tau);
}

constexpr double const Angle::cos() const
{
	return std::cos(Data);
}

constexpr double const Angle::sin() const
{
	return std::sin(Data);
}

