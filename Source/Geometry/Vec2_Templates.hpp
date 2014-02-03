// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "Vec2.h"
#include <Springbok/Math/Operations.h>

template<typename T>
constexpr Vec2<T>::operator bool() const
{
	return X || Y;
}

template<typename T>
T& Vec2<T>::operator[](int i)
{
	return Val[i];
}

template<typename T>
constexpr Vec2<T> Vec2<T>::operator-() const
{
	return Vec2<T>(-X, -Y);
}

template<typename T>
constexpr float Vec2<T>::getLength() const
{
	return SquareRoot((X * X) + (Y * Y));
}

template<typename T>
constexpr Radian Vec2<T>::getAngle(Vec2<T> up) const
{
	return Atan2(Y, X) - Atan2(up.Y, up.X);
}

template<typename T>
Vec2<T> Vec2<T>::rotated(Radian angle, Vec2<T> up) const
{
	float length = getLength();
	Radian myAngle = getAngle(up);
	return Vec2<T>(length * Sin(myAngle + angle), length * -Cos(myAngle + angle));
}

template<typename T>
Vec2<T> Vec2<T>::normalized() const
{
	float length = getLength();
	if(length != 0)
		return (*this) / length;
	else
		return *this;
}

template<typename T>
constexpr float Vec2<T>::dot(Vec2<T> other) const
{
	return X * other.X + Y * other.Y;
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