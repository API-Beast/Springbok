// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <string>

#include <Geometry/Rect.h>

class Texture;

//! @addtogroup Graphics
//! @{

class Image
{
public:
	Image(const std::string& filename);
	Image(){};
	void draw();
	void drawStretched(Vec2< int > size);
	Vec2<int> getSize();
private:
	Texture* mTexture = nullptr;
	RectF mTexCoords = RectF(0.0, 0.0, 1.f, 1.f);
	Vec2<int> mSize = Vec2<int>(0, 0);
};

//! @}