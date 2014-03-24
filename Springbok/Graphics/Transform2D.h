//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <Springbok/Geometry/Vec2.h>
#include <Springbok/Geometry/Angle.h>
#include "VertexStruct.h"
#include <Springbok/Utils/Debug.h>

struct Transform2D
{
	Transform2D() = default;
	Transform2D(Vec2I pos, Angle rotation = 0.0_turn, Vec2F scale = 1, Vec2F alignment = 0.5f, Vec2F parallaxity = 1.f);
	Transform2D(Vec2I pos, Vec2F scale, Vec2F alignment = 0.5f, Vec2F parallaxity = 1.f);
	
	template<class V = BasicVertex>
 	void transform(V* startVertex, V* endVertex, Vec2F cameraPos = 0, Vec2F coordinateMult = 1) const;
	
	Transform2D operator+(const Transform2D& other) const;
	Transform2D operator-(const Transform2D& other) const;
	
	Vec2I Offset       = 0;
	Vec2F Scale        = 1;
	Vec2F Alignment    = 0.5f;
	Angle Rotation     = 0.0_turn;
	Vec2F Parallaxity  = 1.f;
};


template<class V>
void Transform2D::transform(V* startVertex, V* endVertex, Vec2F cameraPos, Vec2F coordinateMult) const
{
	Vec2F minPos(9999999, 9999999);
	Vec2F maxPos;
	Vec2F size;
	
	// Preprocessing
	for(V* it = startVertex; it < endVertex; ++it)
	{
		auto pos = it->Position;
		// Calculate Size for alignment.
		minPos = minPos.upperBound(pos);
		maxPos = maxPos.lowerBound(pos);
	}
	size = maxPos - minPos;
	
	auto calcNewPos = [&](Vec2F position){ return (Rotation.rotateVec(position - size*Alignment)*Scale + Offset - cameraPos * Parallaxity)*coordinateMult; };
	
	// And finally transform
	for(V* it = startVertex; it < endVertex; ++it)
		it->Position = calcNewPos(it->Position);
}