// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <Springbok/Geometry/Angle.h>
#include <Springbok/Geometry/Vec2.h>
#include <Springbok/Geometry/Rect.h>

#include "Color.h"

class Camera;
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
	Vec2I Offset    = Vec2I(0, 0);
	Vec2F Scale     = Vec2F(+1.0f, +1.0f);
	Vec2F Alignment = Vec2F(+0.5f, +0.5f);
	Vec2F RenderTargetOrigin = Vec2F(0, 0);
	Vec2F RenderTargetSize = Vec2F(0, 0);
	Vec2F CameraPos = Vec2F(0, 0);
	Vec2F Parallaxity = Vec2F(1, 1);
	Angle Rotation  = 0.0_turn;
	static unsigned LastBoundTexture;
public:
//!@name Static
///@{
	static void Setup2DEnvironment();
///@}
public:
	RenderContext();
	RenderContext(const RenderContext& parent);
	~RenderContext();
	template<typename T>
	Rect<T> getTransformedRect(Vec2<T> pos, Vec2<T> size) const;
	void setOffsetRelativeToViewport(Vec2I pos);
	void setColor(const Color& color, float alpha=1.f);
	void setBlendingMode(BlendingMode mode);
	void loadDefaults();
	const void draw(unsigned int buffer);
	void initShader();
	Camera* getDefaultCamera() const { return defaultCamera; }
private:
	Camera* defaultCamera;
	Shader* shader;
	const RenderContext* mParent = nullptr;
	Color mSetColor = Colors::White;
	float mSetAlpha = 1.f;
	BlendingMode mSetBlendingMode = Default;
};

template<typename T>
Rect<T> RenderContext::getTransformedRect(Vec2<T> pos, Vec2<T> size) const
{
	Vec2<T> alignment = size*Scale*Alignment;
	Rect<T> result = Rect<T>(-alignment, size*Scale);
	result = result.rotated(Rotation);
	result = result.moved(Offset+pos-(CameraPos*Parallaxity));
	return result;
}
