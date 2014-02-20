//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "Vec3.h"
#include "../Math/Operations.h"

template<typename T>
constexpr bool Vec3<T>::isNull() const
{
	return !X && !Y && !Z;
}

template<typename T>
T& Vec3<T>::operator[](int i)
{
	return Val[i];
}

template<typename T>
const T& Vec3<T>::operator[](int i) const
{
	return Val[i];
}

template<typename T>
constexpr Vec3<T> Vec3<T>::operator-() const
{
	return Vec3<T>(-X, -Y);
}

template<typename T>
constexpr float Vec3<T>::getLength() const
{
	return SquareRoot((X * X) + (Y * Y) + (Z * Z));
}

template<typename T>
Vec3<T> Vec3<T>::lowerBound(Vec3<T> other) const
{
	return Vec3<T>{Max(X, other.X), Max(Y, other.Y), Max(Z, other.Z)};
}

template<typename T>
Vec3<T> Vec3<T>::upperBound(Vec3<T> other) const
{
	return Vec3<T>{Min(X, other.X), Min(Y, other.Y), Min(Z, other.Z)};
}

template<typename T>
constexpr Vec3<T> Vec3<T>::normalized() const
{
	return (*this) / (getLength() || 1);
}