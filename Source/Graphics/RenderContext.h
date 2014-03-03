// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <Springbok/Geometry/Angle.h>
#include <Springbok/Geometry/Vec2.h>
#include <Springbok/Geometry/Rect.h>
#include <Springbok/Graphics/GLTypes.h>
#include <Springbok/Containers/VertexArray.h>

#include "Color.h"
#include "RenderParameters.h"

class Shader;

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
	Vec2F CoordinateOrigin = Vec2F(-1,-1); // In screen space
	Vec2I Size      = Vec2I(800,600);
	Vec2F RenderTargetOrigin = Vec2F(0, 0);
	Vec2F RenderTargetSize = Vec2F(0, 0);
	Vec2F CameraPos = Vec2F(0, 0);
	static unsigned LastBoundTexture;
public:
//!@name Static
///@{
	static void Setup2DEnvironment();
///@}
public:
	RenderContext();
	RenderContext(int width, int height);
	RenderContext(const RenderContext& parent);
	~RenderContext();
	template<typename T>
	Rect<T> getTransformedRect(Vec2<T> pos, Vec2<T> size) const;
	VertexArray<4> transformRect(RectF rect, RenderParameters params);
	void setOffsetRelativeToViewport(Vec2I pos);
	void setColor(const Color& color, float alpha=1.f);
	void setBlendingMode(BlendingMode mode);
	void loadDefaults();
private:
	const RenderContext* mParent = nullptr;
	Color mSetColor = Colors::White;
	float mSetAlpha = 1.f;
	BlendingMode mSetBlendingMode = Default;
};
