// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#include "RenderContext.h"
#include <GL/glew.h>
#include <Springbok/Generic/PointerGuard.h>
#include "Shader.h"
#include "Camera.h"

glHandle vertexArrayHandle;

unsigned RenderContext::LastBoundTexture = 0;

void RenderContext::Setup2DEnvironment()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void RenderContext::loadDefaults()
{
	CameraPos = Vec2F(0, 0);
	LastBoundTexture = 0;
}

void RenderContext::setColor(const Color& color, float alpha)
{
	mSetColor = color;
	mSetAlpha = alpha;
	Color clipped = color.lowerBound(0.f).upperBound(1.f);
}

void RenderContext::setBlendingMode(RenderContext::BlendingMode mode)
{
	mSetBlendingMode = mode;
	if(mode == Default)
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	else if(mode == Additive)
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	else if(mode == Multiplicative)
		glBlendFunc(GL_DST_COLOR, GL_ZERO);
}

VertexArray<4> RenderContext::transformRect(RectF rect, RenderParameters params)
{
	VertexArray<4> output;
	
	int halfWidth = this->Size.X / 2;
	int halfHeight = this->Size.Y / 2;
	float xPixelFactor = 1.0f / halfWidth;
	float yPixelFactor = 1.0f / halfHeight;
	
	Vec2F origin = rect.getOrigin();
	Vec2F size = rect.getSize();
	
	float left 		= (xPixelFactor * (params.Offset.X + this->CameraPos.X + origin.X)) + this->CoordinateOrigin.X;
	float right 	= (xPixelFactor * (params.Offset.X + this->CameraPos.X + origin.X + size.X)) + this->CoordinateOrigin.X;
	float down 		= (yPixelFactor * (params.Offset.Y + this->CameraPos.Y + origin.Y)) + this->CoordinateOrigin.Y;
	float up 		= (yPixelFactor * (params.Offset.Y + this->CameraPos.Y + origin.Y + size.Y)) + this->CoordinateOrigin.Y;

	output[0] = Vec2F(left, down);
	output[1] = Vec2F(right, down);
	output[2] = Vec2F(left, up);
	output[3] = Vec2F(right, up);
	
	return output;
}

RenderContext::RenderContext()
{
	setColor(Colors::White);
}

RenderContext::RenderContext(const RenderContext& parent)
{
	mParent = &parent;
	CameraPos = mParent->CameraPos;
	RenderTargetOrigin = mParent->RenderTargetOrigin;
	RenderTargetSize = mParent->RenderTargetSize;
	mSetColor = mParent->mSetColor;
	mSetAlpha = mParent->mSetAlpha;
	mSetBlendingMode = mParent->mSetBlendingMode;
}

RenderContext::~RenderContext()
{
	if(mParent)
	{
		if((mSetColor != mParent->mSetColor) || (mSetAlpha != mParent->mSetAlpha))
			setColor(mParent->mSetColor, mParent->mSetAlpha);
		if(mSetBlendingMode != mParent->mSetBlendingMode)
			setBlendingMode(mParent->mSetBlendingMode);
	}
}

void RenderContext::setOffsetRelativeToViewport(Vec2< int > pos)
{
};
