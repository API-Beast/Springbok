//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "Vec2.h"
#include "../Math/Range.h"

struct AbstractBoundingShape
{
	virtual RangeF getAxis(int index) const;
};

bool IsIntersecting(const AbstractBoundingShape& a, const AbstractBoundingShape& b);

struct BoundingRect : public AbstractBoundingShape
{
	virtual RangeF getAxis(int index) const { return RangeF(Position[index], Position[index]+Size[index]); };
	BoundingRect(Vec2F pos, Vec2F size){ Position = pos; Size = size; };
	BoundingRect() = default;
	
	Vec2F Position;
	Vec2F Size;
	
	void setCenter(Vec2F center){ Position = center - Size / 2; };
	static BoundingRect FromCenter(Vec2F center, Vec2F size){ return BoundingRect{center-size/2, size}; };
};