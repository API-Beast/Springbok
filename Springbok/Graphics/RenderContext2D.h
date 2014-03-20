// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <Springbok/Geometry/Angle.h>
#include <Springbok/Geometry/Vec2.h>
#include <Springbok/Geometry/Rect.h>

#include "Color.h"
#include "ShaderProgram.h"
#include "RenderTarget.h"
#include "Transform2D.h"

enum class Blending
{
	Default,
	Additive,
	Multiplicative
};

class RenderContext2D
{
public:
	RenderContext2D(RenderTarget* target);
	
	void setShader      (ShaderProgram shader);
	void setBlendingMode(Blending mode);
	void setRenderTarget(RenderTarget* target);
	
	const ShaderProgram& shader()      { return mShader;       };
	      Blending       blendingMode(){ return mBlendingMode; };
	      RenderTarget*  renderTarget(){ return mRenderTarget; };
				
	template<typename T, typename... Args, class U = BasicElement, class V = BasicVertex>
	void draw(const T& object, Transform2D transformation, Args... args, const V& binit = V(), const U& uinit = U());
public:
	Vec2F CameraPos       = 0.0f;
	Vec2F CamaraZoom      = 1.0f;
	Vec2F CameraAlignment = 0.5f;
private:
	Blending       mBlendingMode = Blending::Default;
	ShaderProgram  mShader       = ShaderProgram::GetDefaultShader();
	RenderTarget*  mRenderTarget = nullptr;
};
