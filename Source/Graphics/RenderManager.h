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
//! @{

struct RenderManager
{
public:
	Vec2<int>   Offset    = Vec2<int>(0, 0);
	Vec2F Scale     = Vec2F(+1.0f, +1.0f);
	Vec2F Alignment = Vec2F(+0.5f, +0.5f);
	Vec2F CameraPos = Vec2F(0, 0);
	Radian      Rotation = 0.0f;
	unsigned int LastBoundTexture = 0;
public:
//!@name Static
///@{
	static RenderManager* gInstance;
	static RenderManager* GetInstance();
	static void Setup2DEnvironment();
///@}
public:
	~RenderManager();
  template<typename T>
  Rect<T> getTransformedRect(Vec2<T> pos, Vec2<T> size);
	void setOffsetRelativeToViewport(Vec2<int> pos);
	void setColor(const ColorRGB& color, float alpha=1.f);
	void push();
	void pop();
	void loadDefaults();
private:
	RenderManager* mParent = nullptr;
};

//! @}

template<typename T>
Rect<T> RenderManager::getTransformedRect(Vec2<T> pos, Vec2<T> size)
{
  Vec2<T> alignment = size*Scale*Alignment;
  Rect<T> result = Rect<T>(-alignment, size*Scale);
	result = result.rotated(Rotation);
	result = result.moved(Offset+pos-CameraPos);
	return result;
}
