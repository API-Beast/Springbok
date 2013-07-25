// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#include "Image.h"
#include "Texture.h"
#include <Springbok/Resources/ResourceManager.h>
#include "RenderContext.h"
#include <GL/gl.h>
#include <iostream>

Image::Image(const std::string& filename)
{
	mPath = filename;
	lazyLoad();
}

void Image::draw(const RenderContext& r)
{
	lazyLoad();
	
  Rect<int> vertices = r.getTransformedRect(Vec2I(0, 0), mSize);
	
	if(r.LastBoundTexture != mTexture->Index)
	{
		glBindTexture(GL_TEXTURE_2D, mTexture->Index);
		r.LastBoundTexture = mTexture->Index;
	}
	
  static const GLubyte indices[4] = {0, 1, 2, 3};
  glVertexPointer(2, GL_INT, 0, vertices.Points);
  glTexCoordPointer(2, GL_FLOAT, 0, this->mTexCoords.Points);
  glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, indices);
}

void Image::drawStretched(Vec2< int > size, const RenderContext& r)
{
	lazyLoad();
	
  Rect<int> vertices = r.getTransformedRect(Vec2I(0, 0), size);
	
	if(r.LastBoundTexture != mTexture->Index)
	{
		glBindTexture(GL_TEXTURE_2D, mTexture->Index);
		r.LastBoundTexture = mTexture->Index;
	}
	
  static const GLubyte indices[4] = {0, 1, 2, 3};
  glVertexPointer(2, GL_INT, 0, vertices.Points);
  glTexCoordPointer(2, GL_FLOAT, 0, this->mTexCoords.Points);
  glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, indices);
}

Vec2< int > Image::getSize()
{
	lazyLoad();
	
	return mSize;
}

void Image::lazyLoad()
{
	if(mTexture != nullptr)
		if(mTexture->Valid)
			return ;
		
	mTexture = ResourceManager::GetInstance()->getResource<Texture>(mPath, true);
	if(mTexture->Valid == false)
		return;
	
	mTexCoords = mTexture->TextureCoordinates;
	mSize = Vec2<int>(mTexture->Width, mTexture->Height);
}
