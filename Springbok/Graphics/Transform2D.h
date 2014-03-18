//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <Springbok/Geometry/Vec2.h>
#include <Springbok/Geometry/Angle.h>
#include "VertexArray.h"

struct Transform2D
{
	Transform2D() = default;
	Transform2D(Vec2I pos, Angle rotation = 0.0_turn, Vec2F scale = 1, Vec2F alignment = 0.5f, Vec2F parallaxity = 1.f);
	
	Transform2D(const Transform2D& parent);
	
	template<class V = BasicVertex, class U = BasicElement>
	void transform(V*& vertices, U*& elements, int numElements) const;
	
	Transform2D operator+(const Transform2D& other) const;
	Transform2D operator-(const Transform2D& other) const;
	
	Vec2I Offset       = 0;
	Vec2F Scale        = 1;
	Vec2F Alignment    = 0.5f;
	Angle Rotation     = 0.0_turn;
	Vec2F Parallaxity = 1.f;
};