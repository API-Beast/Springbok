//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "Vec4.h"
#include <cmath>

template<typename T>
constexpr bool Vec4<T>::isNull() const
{
	return !X && !Y && !Z && !W;
}

template<typename T>
T& Vec4<T>::operator[](int i)
{
	return Val[i];
}

template<typename T>
constexpr const T& Vec4<T>::operator[](int i) const
{
	return Val[i];
}

template<typename T>
constexpr Vec4<T> Vec4<T>::operator-() const
{
	return Vec4<T>(-X, -Y, -Z, -W);
}

template<typename T>
constexpr float Vec4<T>::length() const
{
	return std::sqrt(sqLength());
}

template<typename T>
constexpr float Vec4<T>::sqLength() const
{
	return (X * X) + (Y * Y) + (Z * Z) + (W * W);
}

template<typename T>
Vec4<T> Vec4<T>::lowerBound(Vec4<T> other) const
{
	return Vec4<T>{Max(X, other.X), Max(Y, other.Y), Max(Z, other.Z), Max(W, other.W)};
}

template<typename T>
Vec4<T> Vec4<T>::upperBound(Vec4<T> other) const
{
	return Vec4<T>{Min(X, other.X), Min(Y, other.Y), Min(Z, other.Z), Min(W, other.W)};
}

template<typename T>
constexpr Vec4<float> Vec4<T>::normalized() const
{
	return length() > 0 ? ((*this) / length()) : Vec4<T>(0);
}

template<typename T>
constexpr T Vec4<T>::sum() const
{
	return X + Y + Z + W;
}