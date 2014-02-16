// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <string>

#include <Springbok/Geometry/Rect.h>
#include <Springbok/Generic/ObjectPointer.h>

class RenderContext;

class Texture;

//! @addtogroup Graphics
//! @{

class Image
{
public:
	Image(const std::string& filename);
	Image(const Image& other, Vec2I position, Vec2I size);
	Image(){};
	void draw(const RenderContext& r);
	void drawStretched(Vec2I size, const RenderContext& r);
	void drawRepeated(const RenderContext& r);
	void drawRepeated(const RenderContext& context, Vec2F clippingPos, Vec2F clippingSize);
	Vec2<int> getSize();
	Image cut(Vec2I position, Vec2I size);
private:
	void lazyLoad();
	ObjectPointer<Texture> mTexture = nullptr;
	std::string mPath;
	RectF mTexCoords = RectF(0.0, 0.0, 1.f, 1.f);
	Vec2<int> mOffset = Vec2<int>(0, 0);
	Vec2<int> mSize = Vec2<int>(0, 0);
};

//! @}