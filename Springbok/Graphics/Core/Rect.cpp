// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#include "Rect.h"

Rect::Rect(float x, float y, float width, float height)
{
	Points[0].X = x;
	Points[0].Y = y;
	Points[1].X = x + width;
	Points[1].Y = y;
	Points[2].X = x;
	Points[2].Y = y + height;
	Points[3].X = x + width;
	Points[3].Y = y + height;
};

Vec2F Rect::size() const
{
	return Points[3] - Points[0];
};