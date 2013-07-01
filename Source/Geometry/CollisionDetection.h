// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once
#include "Vec2.h"
#include "Rect.h"

struct CollisionCheckResult
{
	operator bool() { return isCollided;     };
	operator Vec2F(){ return collisionPoint; };
	bool  isCollided = false;
	float collisionTime = 0.0f;
	Vec2F collisionPoint = 0.0f;
};

CollisionCheckResult GetCollisionBetween(RectF A, RectF B, Vec2F movementA, Vec2F movementB);