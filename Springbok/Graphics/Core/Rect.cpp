// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#include "Rect.h"

Rect::Rect(float x, float y, float width, float height)
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

Vec2F Rect::size() const
{
	return Points[3] - Points[0];
};