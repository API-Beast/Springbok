// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "Rect.h"

template<typename T>
Rect<T>::Rect(T x, T y, T width, T height)
{
	set(x, y, width, height);
};

template<typename T>
Rect<T>::Rect(Vec2<T> pos, Vec2<T> size)
{
	set(pos, size);
};

template<typename T>
Rect<T>::operator bool() const
{
	return Points[0] != Points[1] && Points[2] != Points[3];
};

template<typename T>
void Rect<T>::set(Vec2<T> pos, Vec2<T> size)
{
	set(pos.X, pos.Y, size.X, size.Y);
};

template<typename T>
void Rect<T>::set(T x, T y, T width, T height)
{
	Points[0][0] = x;
	Points[0][1] = y;
	Points[1][0] = x + width;
	Points[1][1] = y;
	Points[2][0] = x;
	Points[2][1] = y + height;
	Points[3][0] = x + width;
	Points[3][1] = y + height;
};

template<typename T>
Rect<T> Rect<T>::rotated(Radian rotation) const
{
	Rect<T> copy = *this;
	for(Vec2<T>& point : copy.Points)
		point = point.rotated(rotation);
	return copy;
};

template<typename T>
Rect<T> Rect<T>::moved(Vec2<T> movement) const
{
	Rect<T> copy = *this;
	for(Vec2<T>& point : copy.Points)
		point += movement;
	return copy;
};

template<typename T>
Rect<T> Rect<T>::grown(Vec2<T> growth) const
{
	Rect<T> copy = *this;
	copy.set(getOrigin() - growth, getSize() + growth * 2);
	return copy;
};

template<typename T>
Rect<T> Rect<T>::mirroredHorizontal() const
{
	Rect<T> copy = *this;
	copy.Top.Left     = Top.right;
	copy.Bottom.Left  = Bottom.right;
	copy.Top.Right    = Top.left;
	copy.Bottom.Right = Bottom.left;
	return copy;
};

template<typename T>
Rect<T> Rect<T>::mirroredVertical() const
{
	Rect<T> copy = *this;
	copy.Top    = Bottom;
	copy.Bottom = Top;
	return copy;
};

template<typename T>
Vec2<T> Rect<T>::getSize() const
{
	return Points[3] - Points[0];
};

template<typename T>
Vec2<T> Rect<T>::getOrigin() const
{
	return Points[0];
};

template<typename T>
Vec2<T> Rect<T>::getCenter() const
{
	return (Points[0] + Points[3]) / 2;
};

template<typename T>
template<typename P>
bool Rect<T>::isInside(Vec2<P> pos) const
{
	return (Points[0] < pos) && (pos < Points[3]);
}
