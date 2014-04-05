// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

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
constexpr T Min(T a, T b)
{
	return (a < b) ? a : b;
};

template<typename T>
constexpr T Max(T a, T b)
{
	return (a < b) ? b : a;
};

/** Returns the maximum of all arguments.
 * Examples:
 * ~~~
 * Max(12, 3);        // -> 12
 * Max(3, 6, 9, 1);   // -> 9
 * Max(0.62f, 12.0f); // -> 12.0f
 * ~~~
 */
template<typename T, typename... Args>
constexpr T Max(T a, T b, Args... c)
{
	return Max(Max(a, b), c...);
};

/** Returns the minimum of all arguments.
 * Examples:
 * ~~~
 * Min(12, 3);        // -> 3
 * Min(3, 6, 9, 1);   // -> 1
 * Min(0.62f, 12.0f); // -> 0.62f
 * ~~~
 */
template<typename T, typename... Args>
constexpr T Min(T a, T b, Args... c)
{
	return Min(Min(a, b), c...);
};

/** Returns \a value clipped to the \a lowerBound...upperBound range.
 * \a value will be returned if it is between \a lowerBound and \a upperBound. If it is smaller than \a lowerBound, \a lowerBound will be returned, if it is bigger \a upperBound will be returned instead.
 */
template<typename T>
constexpr T BoundBy(T lowerBound, T value, T upperBound)
{
	return (value < lowerBound) ? lowerBound : ((upperBound < value) ? upperBound : value);
};

template<typename T>
constexpr T Abs(const T val)
{
	return (val > T()) ? val : -val;
}

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

template<template<class> class T, class A, class B>
constexpr auto Modulo(const T<A>& a, const T<B>& b) -> decltype(a - (b * T<int>(a/b)))
{
	return a - (b * T<int>(a/b));
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

template<typename T>
T NextBiggerValue(T val)
{
	return val + 1;
};

template<>
inline float NextBiggerValue(float val)
{
	return std::nextafterf(val, INFINITY);
};

template<>
inline double NextBiggerValue(double val)
{
	return std::nextafter(val, INFINITY);
};

template<>
inline long double NextBiggerValue(long double val)
{
	return std::nextafterl(val, INFINITY);
};

template<typename T>
T NextSmallerValue(T val)
{
	return val - 1;
};

template<>
inline float NextSmallerValue(float val)
{
	return std::nextafterf(val, -INFINITY);
};

template<>
inline double NextSmallerValue(double val)
{
	return std::nextafter(val, -INFINITY);
};

template<>
inline long double NextSmallerValue(long double val)
{
	return std::nextafterl(val, -INFINITY);
};

//@}