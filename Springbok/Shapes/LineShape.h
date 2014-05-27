//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once
#include <Springbok/Types/Vec4.h>
#include <Springbok/Geometry/Rect.h>
#include <Springbok/Containers/List.h>
#include <Springbok/Graphics/Core/VertexStruct.h>
#include <Springbok/Graphics/Image.h>

struct LineShape
{
public:
	struct Point
	{
		Vec2F Position = 0.f;
		float    Width = 1.f;
		float TexCoord = 0.f;
		Vec4F Color    = {1, 1, 1, 1};
	};
public:
	List<Point>   Points;
	Image       TexImage;
public:
	void  insert(Vec2F position, float width=3, Vec4F color=1);
	void  divideEquidistant(float pixels);
	void  applyTexture(const Image& img, float repetitions = 1.f);
	float calcLength();
public:
	template<class V = BasicVertex, class E = BasicElement>
	void prepareVertices(RenderDataPointer< V, E >& data) const;
};

#include "LineShape_Templates.hpp"