//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include "SpriteRenderer.h"

#pragma once

template<typename T>
void SpriteRenderer::draw(const T& obj, Vec2F position, Vec4F color, Blending mode, Transform2D transformation)
{
	Batcher.draw(obj, Position2D(position) + transformation, BasicVertex(color), BasicElement(mode));
}

template<typename T>
void SpriteRenderer::draw(const T& obj, Transform2D transformation, Vec4F color, Blending mode)
{
	Batcher.draw(obj, transformation, BasicVertex(color), BasicElement(mode));
}

template<typename T>
void SpriteRenderer::drawRepeatedInf(const T& obj, Vec2F offset, Vec2F scale, Vec2F parralaxity, Vec4F color, Blending mode)
{
	CameraData oldCam = Context.Camera;
	offset -= Context.cameraCenter() * parralaxity;
	scale  *= oldCam.Zoom;
	offset *= oldCam.Zoom;
	
	Context.Camera = CameraData();
	Context.Camera.Position  = 0.f;
	
	Vec2F size = obj.size() * scale;
	Vec2I max = (Context.renderTarget()->size() / size) + 8;
	Vec2I i;
	offset = Modulo(offset, size);
	
	for(i.X = -max.X/2; i.X < max.X/2; ++i.X)
		for(i.Y = -max.Y/2; i.Y < max.Y/2; ++i.Y)
			Batcher.draw(obj, Position2D(offset) + Position2D(size * i) + Scale2D(scale), BasicVertex(color), BasicElement(mode));

	Context.Camera = oldCam;
}

template<typename T>
void SpriteRenderer::drawStretched(const T& obj, Vec2F position, Vec2F size, Vec4F color, Blending mode, Transform2D transformation)
{
	Batcher.draw(obj, Position2D(position) + transformation + Scale2D(obj.size() / size), BasicVertex(color), BasicElement(mode));
}