//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include "BoundingShapes.h"

RangeF AbstractBoundingShape::getAxis(int index) const
{

}

bool IsIntersecting(const AbstractBoundingShape& a, const AbstractBoundingShape& b)
{
	for(int i = 0; i < 2; ++i)
		if(!a.getAxis(i).getIntersection(b.getAxis(i)))
			return false;
	return true;
}
