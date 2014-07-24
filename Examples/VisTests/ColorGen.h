//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "VisTest.h"
#include <Springbok/Graphics/Image.h>

struct ColorGen : public VisTest
{
	Image Blob;
  double x=0;
	double y=0;
	
	virtual void draw(float deltaTime, SpriteRenderer& r);
	virtual void initialize();
	virtual void onClick(Vec2F pos);
	virtual void onIncrement();
	virtual void onDecrement();
	virtual std::string description(){ return "Click to change base color."; };
	virtual std::string status(){ return "Color Generator: Hue " + std::to_string(x) + " Chroma " + std::to_string(y); };
};