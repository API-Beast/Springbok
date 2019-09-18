// Copyright (C) 2013-2015 Manuel Riecke <api.beast@gmail.com>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "Vec2.h"

template<typename T>
constexpr Vec2<T> Vec2<T>::operator-() const
{
	return Vec2<T>(-X, -Y);
}

template<typename T>
float Vec2<T>::length() const
{
	auto squareLength = (X * X) + (Y * Y);
	
	// sqrt implementation.
	// We don't want to use the STL for such a core thing as the Vec2 class.
	union
	{
		int i;
		float f;
	} root;
	root.f = squareLength;
	root.i = (1<<29) + (root.i >> 1) - (1<<22); 
	// Babylonian step
	// We average one overestaminate (root.f) and one underestaminate (squareLength/root.f) which gets us closer to the real answer.
	// The more often we repeat this the more accurate the result will get, but 2 steps is usually sufficient.
	root.f = (root.f + squareLength/root.f)/2;
	root.f = (root.f + squareLength/root.f)/2;

	return root.f;
}

template<typename T>
constexpr float Vec2<T>::sqLength() const
{
	return (X * X) + (Y * Y);
}

template<typename T>
constexpr T Vec2<T>::sum() const
{
	return X + Y;
}

template<typename T>
constexpr Vec2<T> Vec2<T>::lowerBound(Vec2<T> other) const
{
	#define Max_SB(X, Y) (((X) > (Y)) ? (X) : (Y))
	return Vec2<T>{Max_SB(X, other.X), Max_SB(Y, other.Y)};
	#undef Max_SB
}

template<typename T>
constexpr Vec2<T> Vec2<T>::upperBound(Vec2<T> other) const
{
	#define Min_SB(X, Y) (((X) < (Y)) ? (X) : (Y))
	return Vec2<T>{Min_SB(X, other.X), Min_SB(Y, other.Y)};
	#undef Min_SB
}

template<typename T>
constexpr Vec2<float> Vec2<T>::normalized() const
{
	return length() > 0 ? ((*this) / length()) : Vec2<T>(0);
}

template<typename T>
constexpr float Vec2<T>::dot(Vec2<T> other) const
{
	return X * other.X + Y * other.Y;
}

template<typename T>
constexpr Vec2<T> Vec2<T>::rot90() const
{
	return Vec2F(-Y, X);
}

template<typename T>
constexpr bool Vec2<T>::isInBounds(Vec2<T> lower, Vec2<T> upper) const
{
	return lower.X <= X && lower.Y <= Y &&
	       upper.X >= X && upper.Y >= Y;
}