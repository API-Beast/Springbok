//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <vector>
#include <Springbok/Geometry/Vec4.h>
#include "Color.h"

struct BasicVertex;
struct BasicUniforms;

template<class Vertex = BasicVertex, class PropertySet = BasicUniforms>
struct VertexArray
{
	std::vector<Vertex> Vertices;
	PropertySet Properties;
};

struct BasicVertex
{
	Vec2F Position  = 0.f;
	Vec2F TexCoords = 0.f;
	Vec4F Color     = Colors::White;
};

struct BasicUniforms
{
	int Texture = 0;
};