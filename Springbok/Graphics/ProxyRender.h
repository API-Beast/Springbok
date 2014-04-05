//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "VertexStruct.h"
#include "Transform2D.h"

template<class T, class R, class E=BasicElement, class V=BasicVertex>
void DrawGridPattern(R& renderer, T& obj, Vec2I size, Transform2D baseTransform = Transform2D(), Transform2D perElementTransform = Transform2D(), const V& vertex = V(), const E& element = E())
{
	Vec2I current = 0;
	Transform2D currentRowTransform = baseTransform;
	while(current.Y < size.Y)
	{
		Transform2D currentCellTransform;
		currentRowTransform += perElementTransform.yOnly();
		currentCellTransform = currentRowTransform;
		
		current.Y++;
		current.X = 0;
		
		while(current.X < size.X)
		{
			current.X++;
			currentCellTransform += perElementTransform.xOnly();
			renderer.draw(obj, currentCellTransform, vertex, element);
		}
	}
}