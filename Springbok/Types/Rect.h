// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <Springbok/Types/Vec2.h>
#include <Springbok/Types/Angle.h>

struct Rect
{
	Vec2F Points[4];
	
public:
	Rect(float x, float y, float width, float height);
	Rect() : Rect(0, 0, 0, 0){};
	Rect(Vec2F pos, Vec2F size) : Rect(pos.X, pos.Y, size.X, size.Y){};
	
	Vec2F size() const;
	bool pointInside(Vec2F pos) const;
};