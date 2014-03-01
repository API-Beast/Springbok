// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "Vec2.h"
#include "Angle.h"
#include "Rect.h"

template<typename T>
struct TexRect
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
	TexRect() {};
	TexRect(T x, T y, T width, T height);
	TexRect(Vec2<T> pos, Vec2<T> size);
	/** Returns \c true if the rectangle has a size != 0. */
	operator bool() const;
	void set(Vec2<T> pos, Vec2<T> size);
	void set(T x, T y, T width, T height);
	TexRect<T> rotated(Angle rotation) const;
	TexRect<T> moved(Vec2<T> movement) const;
	TexRect<T> grown(Vec2<T> growth) const;
	TexRect<T> mirroredHorizontal() const;
	TexRect<T> mirroredVertical() const;
	TexRect<T> getIntersection(TexRect<T> other) const;
	TexRect<T> getUnion(TexRect<T> other) const;
	Vec2<T> getSize()   const;
	Vec2<T> getOrigin() const;
	Vec2<T> getCenter() const;
	template<typename P> bool isInside(Vec2<P> pos) const;
};

using TexRectF = TexRect<float>;

#include "TexRect_Templates.hpp"
