// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <Springbok/Geometry/Angle.h>
#include <Springbok/Geometry/Vec2.h>
#include <Springbok/Geometry/Rect.h>

#include "Color.h"

//! @addtogroup Graphics
struct RenderContext
{
public:
	enum BlendingMode
	{
		Default,
		Additive,
		Multiplicative
	};
public:
	Vec2F CameraPos   = 0;
	Vec2F Zoom        = 1;
	Vec2F Parallaxity = 1;
	
	Vec2F RenderTargetOrigin = 0;
	Vec2F RenderTargetSize   = 0;
public:
	BlendingMode getBlendingMode();
	void setBlendingMode(BlendingMode mode);
private:
	const RenderContext* mParent = nullptr;
	Color mSetColor = Colors::White;
	float mSetAlpha = 1.f;
	BlendingMode mSetBlendingMode = Default;
};
