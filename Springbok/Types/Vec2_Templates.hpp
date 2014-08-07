// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "Vec2.h"
#include <Springbok/Math/Operations.h>

template<typename T>
constexpr bool Vec2<T>::isNull() const
{
	return !X && !Y;
}

template<typename T>
T& Vec2<T>::operator[](int i)
{
	return Val[i];
}

template<typename T>
constexpr const T& Vec2<T>::operator[](int i) const
{
	return Val[i];
}

template<typename T>
constexpr Vec2<T> Vec2<T>::operator-() const
{
	return Vec2<T>(-X, -Y);
}

template<typename T>
constexpr float Vec2<T>::length() const
{
	return SquareRoot((X * X) + (Y * Y));
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
Vec2<T> Vec2<T>::lowerBound(Vec2<T> other) const
{
	return Vec2<T>{Max(X, other.X), Max(Y, other.Y)};
}

template<typename T>
Vec2<T> Vec2<T>::upperBound(Vec2<T> other) const
{
	return Vec2<T>{Min(X, other.X), Min(Y, other.Y)};
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

/*template<typename T>
Vec2<T> Vec2<T>::projected(Vec2<T> line) const
{
	return this->dot(line.normalize()) * (*this);
}*/

template<typename T>
float Vec2<T>::projectAxis(Vec2<T> axis) const
{
	return (this->dot(axis) * (*this)).getLength();
}

template<typename T>
bool Vec2<T>::isInBounds(Vec2<T> lower, Vec2<T> upper)
{
	return lower.X <= X && lower.Y <= Y &&
	       upper.X >= X && upper.Y >= Y;
}