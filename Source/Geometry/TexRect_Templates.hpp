// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "TexRect.h"

template<typename T>
TexRect<T>::TexRect(T x, T y, T width, T height)
{
	set(x, y, width, height);
};

template<typename T>
TexRect<T>::TexRect(Vec2<T> pos, Vec2<T> size)
{
	set(pos, size);
};

template<typename T>
TexRect<T>::operator bool() const
{
	return Points[0] != Points[1] && Points[2] != Points[3];
};

template<typename T>
void TexRect<T>::set(Vec2<T> pos, Vec2<T> size)
{
	set(pos.X, pos.Y, size.X, size.Y);
};

template<typename T>
void TexRect<T>::set(T x, T y, T width, T height)
{
	Points[0][0] = x;
	Points[0][1] = y;
	Points[1][0] = x;
	Points[1][1] = y + height;
	Points[2][0] = x + width;
	Points[2][1] = y + height;
	Points[3][0] = x + width;
	Points[3][1] = y;
};

template<typename T>
TexRect<T> TexRect<T>::rotated(Angle rotation) const
{
	TexRect<T> copy = *this;
	for(Vec2<T>& point : copy.Points)
		point = rotation.rotateVec(point);
	return copy;
};

template<typename T>
TexRect<T> TexRect<T>::moved(Vec2<T> movement) const
{
	TexRect<T> copy = *this;
	for(Vec2<T>& point : copy.Points)
		point += movement;
	return copy;
};

template<typename T>
TexRect<T> TexRect<T>::grown(Vec2<T> growth) const
{
	TexRect<T> copy = *this;
	copy.set(getOrigin() - growth, getSize() + growth * 2);
	return copy;
};

template<typename T>
TexRect<T> TexRect<T>::mirroredHorizontal() const
{
	TexRect<T> copy = *this;
	copy.Top.Left     = Top.right;
	copy.Bottom.Left  = Bottom.right;
	copy.Top.Right    = Top.left;
	copy.Bottom.Right = Bottom.left;
	return copy;
};

template<typename T>
TexRect<T> TexRect<T>::mirroredVertical() const
{
	TexRect<T> copy = *this;
	copy.Top    = Bottom;
	copy.Bottom = Top;
	return copy;
};

template<typename T>
Vec2<T> TexRect<T>::getSize() const
{
	return Points[3] - Points[0];
};

template<typename T>
Vec2<T> TexRect<T>::getOrigin() const
{
	return Points[0];
};

template<typename T>
Vec2<T> TexRect<T>::getCenter() const
{
	return (Points[0] + Points[3]) / 2;
};

template<typename T>
template<typename P>
bool TexRect<T>::isInside(Vec2<P> pos) const
{
	return (Points[0] < pos) && (pos < Points[3]);
}
