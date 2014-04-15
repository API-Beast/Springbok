//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "VisTest.h"
#include <Springbok/Graphics/SpriteRenderer.h>
#include <Springbok/Shapes/LineShape.h>

struct LineDrawing : public VisTest
{
	LineShape Line;
	LineShape LineSubdivided;
	float LastClickTimer = 0;
	
	virtual void initialize();
	virtual void draw(float deltaTime, SpriteRenderer& r);
	virtual void onClick(Vec2F pos);
};
