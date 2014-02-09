// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#include "RenderContext.h"
#include <GL/gl.h>
#include <Springbok/Generic/PointerGuard.h>

unsigned RenderContext::LastBoundTexture = 0;

void RenderContext::Setup2DEnvironment()
{
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glAlphaFunc(GL_ALWAYS, 0);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}

void RenderContext::loadDefaults()
{
	Offset    = Vec2<int>(0, 0);
	Scale     = Vec2F(+1.0f, +1.0f);
	Alignment = Vec2F(+0.5f, +0.5f);
	CameraPos = Vec2F(0, 0);
	Rotation  = 0.0f;
	LastBoundTexture = 0;
}

void RenderContext::setColor(const ColorRGB& color, float alpha)
{
	mSetColor = color;
	mSetAlpha = alpha;
	glColor4f(color.Red, color.Green, color.Blue, alpha);
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

RenderContext::RenderContext(const RenderContext& parent)
{
	mParent = &parent;
	Offset    = mParent->Offset;
	Scale     = mParent->Scale;
	Alignment = mParent->Alignment;
	CameraPos = mParent->CameraPos;
	Rotation  = mParent->Rotation;
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
  Offset = CameraPos + pos;
};