// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "Functions.h"

#ifndef M_PI
	#define GET_RID_OF_CONSTANTS
#endif

#include <cmath>

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

//! @ingroup Math
//@{

template<typename T>
constexpr int Sign(const T val)
{
	return (val > T()) ? 1 : -1;
}

template<typename A, typename B>
constexpr auto Modulo(const A& a, const B& b) -> decltype(a - (b * int(a/b)))
{
	return a - (b * int(a/b));
}

/** Return \a a if it is positive, else return \a b. */
template<typename T>
constexpr T ChoosePositive(T a, T b)
{
	return (a > 0.f) ? a : b;
};

template<typename A, typename B>
constexpr auto PositiveModulo(const A& a, const B& b) -> decltype(a - (b * int(a/b)))
{
	return ChoosePositive(a - (b * int(a/b)), b - Abs(a - (b * int(a/b))));
}

template<typename A>
constexpr auto Power(const A& a, float n) -> decltype(a * a)
{
	return std::pow(a, n);
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

template<typename A>
constexpr int RoundDown(const A& a)
{
	return a;
}

template<typename A>
constexpr int RoundUp(const A& a)
{
	return a == int(a) ? a : a + 1;
}

template<typename A>
constexpr int Round(const A& a)
{
	return (Modulo(a, 1.0) >= 0.5) ? RoundUp(a) : RoundDown(a);
}

template<typename A, typename B>
constexpr auto RoundDown(const A& a, const B& precision) -> decltype(a - Modulo(a, precision))
{
	return a - Modulo(a, precision);
}

template<typename A, typename B>
constexpr auto RoundUp(const A& a, const B& precision) -> decltype(a - Modulo(a, precision))
{
	return a + (precision - Modulo(a, precision));
}

template<typename A, typename B>
constexpr auto Round(const A& a, const B& precision) -> decltype(a - Modulo(a, precision))
{
	return (Modulo(a, precision) >= precision/2) ? RoundUp(a, precision) : RoundDown(a, precision); 
}

template<typename T>
constexpr T MinAbs(T a, T b)
{
	return (Abs(a) > Abs(b)) ? b : a;
};

template<typename T>
constexpr T MaxAbs(T a, T b)
{
	return (Abs(a) < Abs(b)) ? b : a;
};

template<typename T, typename... Args>
constexpr T MaxAbs(T a, T b, Args... c)
{
	return MaxAbs(MaxAbs(a, b), c...);
};
	
template<typename T, typename... Args>
constexpr T MinAbs(T a, T b, Args... c)
{
	return MinAbs(MaxAbs(a, b), c...);
};

//@}