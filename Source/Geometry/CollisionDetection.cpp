// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#include "CollisionDetection.h"

CollisionCheckResult GetCollisionBetween(RectF A, RectF B, Vec2F movementA, Vec2F movementB)
{
	RectF C = A.grown(B.getSize()/2);
}