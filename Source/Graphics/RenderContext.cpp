// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#include "RenderContext.h"
#include <GL/glew.h>
#include <Springbok/Generic/PointerGuard.h>
#include "Shader.h"
#include "Camera.h"

const char* vertexShader = 
"attribute vec2 VertexPosition;"
""
"void main() {"
"gl_Position.xyz = vec3(VertexPosition.x,VertexPosition.y,0);"
"gl_Position.w = 1.0;"
"}";

const char* fragmentShader =
"void main(){"
"gl_FragColor = vec4(1,0,0,1);"
"}";

glHandle vertexArrayHandle;

unsigned RenderContext::LastBoundTexture = 0;

void RenderContext::Setup2DEnvironment()
{
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glAlphaFunc(GL_ALWAYS, 0);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glGenVertexArrays(1, &vertexArrayHandle);
	glBindVertexArray(vertexArrayHandle);
}

void RenderContext::initShader()
{
	shader = new Shader(vertexShader,fragmentShader);
}

void RenderContext::loadDefaults()
{
	Offset    = Vec2<int>(0, 0);
	Scale     = Vec2F(+1.0f, +1.0f);
	Alignment = Vec2F(+0.5f, +0.5f);
	CameraPos = Vec2F(0, 0);
	Rotation  = 0_turn;
	LastBoundTexture = 0;
}

void RenderContext::setColor(const Color& color, float alpha)
{
	mSetColor = color;
	mSetAlpha = alpha;
	Color clipped = color.lowerBound(0.f).upperBound(1.f);
	//glColor4f(color[0], color[1], color[2], alpha);
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

const void RenderContext::draw(unsigned int buffer)
{
	shader->bind();
	int vertexAttributeLocation = shader->getAttributeLocation("VertexPosition");
	glEnableVertexAttribArray(vertexAttributeLocation);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glVertexAttribPointer(vertexAttributeLocation, 2, GL_FLOAT, false, 0, 0);
	static const GLubyte indices[4] = {0, 1, 2, 3};
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glDisableVertexAttribArray(vertexAttributeLocation);
}

RenderContext::RenderContext()
{
	setColor(Colors::White);
	setBlendingMode(Default);
	defaultCamera = new Camera(800,600);
}

RenderContext::RenderContext(const RenderContext& parent)
{
	mParent = &parent;
	Offset    = mParent->Offset;
	Scale     = mParent->Scale;
	Alignment = mParent->Alignment;
	CameraPos = mParent->CameraPos;
	Rotation  = mParent->Rotation;
	Parallaxity = mParent->Parallaxity;
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
	Offset = CameraPos + pos;
};