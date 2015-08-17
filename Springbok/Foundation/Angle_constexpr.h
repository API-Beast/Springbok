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

constexpr double Angle::cos()
{
	return std::cos(Data);
}

constexpr double Angle::sin()
{
	return std::sin(Data);
}

namespace
{
	constexpr double atan_poly_helper(const double res,  const double num1, const double den1, const double delta)
	{
		return res < .001 ? res :
		       res + atan_poly_helper((num1*delta)/(den1+2.)-num1/den1,
		                              num1*delta*delta,den1+4., delta);
	}

	constexpr double atan_poly(const double x)
	{
		return x + atan_poly_helper((x*x*x*x*x)/5.-(x*x*x)/3., (x*x*x*x*x*x*x), 7., x*x);
	}

	// Define an M_PI_6? Define a root 3?
	constexpr double atan_identity(const double x)
	{
		return x <= (2. - std::sqrt(3)) ? atan_poly(x) :
		       (Pi/6) + atan_poly(std::sqrt(3)*x-1/(std::sqrt(3)+x));
	}

	constexpr double atan_cmplmntry(const double x)
	{
		return (x < 1) ? atan_identity(x) : Pi/2 - atan_identity(1/x);
	}
	
	constexpr double atan_impl(double x)
	{
		return (x >= 0) ? atan_cmplmntry(x) : -atan_cmplmntry(-x);
	}
}

constexpr Angle Angle::Atan2(double a, double b)
{
  return Angle::FromRadians(a >  0 ? atan_impl(b/a)                : 
														b >= 0 && a <  0 ? atan_impl(b/a) + Pi :
														b <  0 && a <  0 ? atan_impl(b/a) - Pi :
														b >  0 && a == 0 ?  Tau/4         :
														b <  0 && a == 0 ? -Tau/4         : 0);   // 0 == undefined
};