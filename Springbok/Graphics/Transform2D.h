//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <Springbok/Geometry/Vec2.h>
#include <Springbok/Geometry/Angle.h>
#include "VertexStruct.h"

struct Transform2D
{
	Transform2D() = default;
	Transform2D(Vec2I pos, Angle rotation = 0.0_turn, Vec2F scale = 1, Vec2F alignment = 0.5f, Vec2F parallaxity = 1.f);
	
	template<class V = BasicVertex>
	void transform(V* vertices, GLushort* indexBegin, GLushort* indexEnd, Vec2F cameraPos = 0, Vec2F coordinateMult = 1) const;
	
	Transform2D operator+(const Transform2D& other) const;
	Transform2D operator-(const Transform2D& other) const;
	
	Vec2I Offset       = 0;
	Vec2F Scale        = 1;
	Vec2F Alignment    = 0.5f;
	Angle Rotation     = 0.0_turn;
	Vec2F Parallaxity  = 1.f;
};


template<class V>
void Transform2D::transform(V* vertices, GLushort* indexBegin, GLushort* indexEnd, Vec2F cameraPos, Vec2F coordinateMult) const
{
	Vec2F minPos(INFINITY);
	Vec2F maxPos;
	Vec2F size;
	GLushort smallestIndex = 64000;
	GLushort biggestIndex  = 0;
	static bool isTransformed[256];
	
	// Preprocessing
	for(GLushort* it = indexBegin; it < indexEnd; ++it)
	{
		auto pos = vertices[*it].Position;
		// Find out what indices are used.
		smallestIndex = Min(smallestIndex, *it);
		biggestIndex = Max(biggestIndex, *it);
		// Calculate Size for alignment.
		minPos.lowerBound(pos);
		maxPos.upperBound(pos);
	}
	size = maxPos - minPos;
	
	// And finally transform
	for(int i = 0; i < (biggestIndex - smallestIndex); ++i)
	{
		auto pos = vertices[smallestIndex+i].Position;
		vertices[smallestIndex+i].Position = (Rotation.rotateVec(pos - size*Alignment)*Scale + Offset - cameraPos * Parallaxity)*coordinateMult;
	}
}