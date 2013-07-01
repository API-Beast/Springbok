// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#ifndef M_PI
	#define GET_RID_OF_CONSTANTS
#endif

#include <cmath>
#include "Radian.h"

// Get rid of the cmath constants
#ifdef GET_RID_OF_CONSTANTS
#ifdef M_PI
	#undef M_E
	#undef M_LOG2E
	#undef M_LOG10E
	#undef M_LN2
	#undef M_LN10
	#undef M_PI
	#undef M_PI_2
	#undef M_PI_4
	#undef M_1_PI
	#undef M_2_PI
	#undef M_2_SQRTPI
	#undef M_SQRT2
	#undef M_SQRT1_2
#endif
#endif
#undef GET_RID_OF_CONSTANTS

template<typename T>
constexpr T Min(T a, T b)
{
	return (a < b) ? a : b;
};

template<typename T>
constexpr T Max(T a, T b)
{
	return (a < b) ? b : a;
};

template<typename T, typename... Args>
constexpr T Max(T a, T b, Args... c)
{
	return Max(Max(a, b), c...);
};
	
template<typename T>
constexpr T BoundBy(T a, T b, T c)
{
	return (b < a) ? a :((c < b) ? c : b);
};

constexpr float Sin(const Radian r)
{
	return std::sin(r);
}

constexpr float Cos(const Radian r)
{
	return std::cos(r);
}

template<typename T>
constexpr const Radian Atan2(const T a, const T b)
{
	return std::atan2(a, b);
}

template<typename T>
constexpr const Radian Acos(const T A)
{
	return std::acos(A);
}

template<typename T>
constexpr const Radian Asin(const T A)
{
	return std::asin(A);
}

template<typename A, typename B>
constexpr auto Modulo(const A& a, const B& b) -> decltype(a - (b * int(a/b)))
{
	return a - (b * int(a/b));
}

template<typename A>
constexpr auto Power(const A& a, float n) -> decltype(a * a)
{
	return std::pow(a, n);
}

template<typename A>
constexpr auto Power(const A& a, int n) -> decltype(a * a)
{
	return (n <= 1) ? a : a * Power(a, n-1);
}

template<int N, typename A>
constexpr auto Power(const A& a) -> decltype(a * a)
{
	return (N <= 1) ? a : a * Power(a, N-1);
}

template<typename A>
constexpr auto Root(const A& a, float n) -> decltype(a / a)
{
	return std::pow(a, 1.f / n);
}

template<int N, typename A>
constexpr auto Root(const A& a) -> decltype(a / a)
{
	return (N == 2) ? std::sqrt(a) : std::pow(a, 1.f / N);
}

template<typename A>
constexpr auto SquareRoot(const A& a) -> decltype(std::sqrt(a))
{
	return std::sqrt(a);
}