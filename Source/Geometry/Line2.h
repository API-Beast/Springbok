// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "Vec2.h"
#include "Angle.h"

/** A simple two dimensional line. */
template<typename T>
struct Line2
{
	Line2(const Vec2<T>& A, const Vec2<T>& B);
	/** Returns true if \a this and \a other cover the same space. */
	bool operator==(const Line2< T >& other) const;
	/** Returns true if \a this and \a other intersect. */
	bool isIntersecting(const Line2< T >& other) const;
	/** Returns the direction of the line. */
	Vec2<T> direction() const;
	/** The starting point of the line. */
	Vec2<T> Start;
	/** The ending point of the line. */
	Vec2<T> End;
};

using Line2F = Line2<float>;
using Line2I = Line2<int>;
using Line2U = Line2<unsigned>;

#include "Line2_Templates.hpp"