// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <Springbok/Geometry/Vec2.h>
#include <Springbok/Geometry/Rect.h>
#include <Springbok/Math/Radian.h>

#include "Color.h"

//! @addtogroup Graphics
struct RenderContext
{
public:
	Vec2I  Offset    = Vec2I(0, 0);
	Vec2F  Scale     = Vec2F(+1.0f, +1.0f);
	Vec2F  Alignment = Vec2F(+0.5f, +0.5f);
	Vec2F  CameraPos = Vec2F(0, 0);
	Radian Rotation  = 0.0f;
	static unsigned LastBoundTexture;
public:
//!@name Static
///@{
	static void Setup2DEnvironment();
///@}
public:
	template<typename T>
	Rect<T> getTransformedRect(Vec2<T> pos, Vec2<T> size) const;
	void setOffsetRelativeToViewport(Vec2I pos);
	void setColor(const ColorRGB& color, float alpha=1.f);
	void loadDefaults();
private:
	RenderContext* mParent = nullptr;
};

template<typename T>
Rect<T> RenderContext::getTransformedRect(Vec2<T> pos, Vec2<T> size) const
{
	Vec2<T> alignment = size*Scale*Alignment;
	Rect<T> result = Rect<T>(-alignment, size*Scale);
	result = result.rotated(Rotation);
	result = result.moved(Offset+pos-CameraPos);
	return result;
}
