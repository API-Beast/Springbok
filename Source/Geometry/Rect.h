// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "Vec2.h"
#include "Angle.h"

/** @cond */
template<typename T>
union HorzSide
{
	Vec2<T> Data[2];
	struct
	{
		Vec2<T> Left;
		Vec2<T> Right;
	};
	Vec2<T>& operator[](int index)
	{
		return Data[index];
	};
};
/** @endcond */
	
template<typename T>
struct Rect
{
public:
	/** @cond */
	union
	{
		Vec2<T> Points[4];
		struct
		{
			HorzSide<T> Top;
			HorzSide<T> Bottom;
		};
	};
	/** @endcond */
public:
	Rect(){};
	Rect(T x, T y, T width, T height);
	Rect(Vec2<T> pos, Vec2<T> size);
	/** Returns \c true if the rectangle has a size != 0. */
	operator bool() const;
	void set(Vec2<T> pos, Vec2<T> size);
	void set(T x, T y, T width, T height);
	Rect<T> rotated(Radian rotation) const;
	Rect<T> moved(Vec2<T> movement) const;
	Rect<T> grown(Vec2<T> growth) const;
	Rect<T> mirroredHorizontal() const;
	Rect<T> mirroredVertical() const;
	Rect<T> getIntersection(Rect<T> other) const;
	Rect<T> getUnion(Rect<T> other) const;
	Vec2<T> getSize()   const;
	Vec2<T> getOrigin() const;
	Vec2<T> getCenter() const;
	template<typename P> bool isInside(Vec2<P> pos) const;
};

using RectF = Rect<float>;

#include "Rect_Templates.hpp"