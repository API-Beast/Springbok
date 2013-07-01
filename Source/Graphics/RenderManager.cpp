// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#include "RenderManager.h"
#include <GL/gl.h>



RenderManager* RenderManager::gInstance = nullptr;

RenderManager::~RenderManager()
{
	delete mParent;
}

RenderManager* RenderManager::GetInstance()
{
	if(gInstance == nullptr)
		gInstance = new RenderManager;
	return gInstance;
}

void RenderManager::loadDefaults()
{
	Offset    = Vec2<int>(0, 0);
	Scale     = Vec2F(+1.0f, +1.0f);
	Alignment = Vec2F(+0.5f, +0.5f);
	CameraPos = Vec2F(0, 0);
	Rotation = 0.0f;
	LastBoundTexture = 0;
}

void RenderManager::setColor(const ColorRGB& color, float alpha)
{
	glColor4f(color.Red, color.Green, color.Blue, alpha);
}

void RenderManager::setOffsetRelativeToViewport(Vec2< int > pos)
{
  Offset = CameraPos + pos;
};

void RenderManager::pop()
{
	if(mParent == nullptr) return;
	*this = *mParent;
	delete mParent;
	mParent = nullptr;
}

void RenderManager::push()
{
	mParent = new RenderManager(*this);
}
