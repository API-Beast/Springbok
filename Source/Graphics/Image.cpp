// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#include "Image.h"
#include <Core/AssetManager.h>
#include <Graphics/RenderManager.h>
#include <GL/gl.h>



Image::Image(const std::string& filename)
{
	mTexture = AssetManager::GetInstance()->Textures[filename];
	mTexCoords = mTexture->TextureCoordinates;
	mSize = Vec2<int>(mTexture->Width, mTexture->Height);
}

void Image::draw()
{
	RenderManager* r = RenderManager::GetInstance();
  Rect<int> vertices = r->getTransformedRect<int>(Vec2<int>(0, 0), mSize);
	
	if(r->LastBoundTexture != mTexture->Index)
	{
		glBindTexture(GL_TEXTURE_2D, mTexture->Index);
		r->LastBoundTexture = mTexture->Index;
	}
	
  static const GLubyte indices[4] = {0, 1, 2, 3};
  glVertexPointer(2, GL_INT, 0, vertices.Points);
  glTexCoordPointer(2, GL_FLOAT, 0, this->mTexCoords.Points);
  glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, indices);
}

void Image::drawStretched(Vec2<int> size)
{
	RenderManager* r = RenderManager::GetInstance();
  Rect<int> vertices = r->getTransformedRect<int>(Vec2<int>(0, 0), size);
	
	if(r->LastBoundTexture != mTexture->Index)
	{
		glBindTexture(GL_TEXTURE_2D, mTexture->Index);
		r->LastBoundTexture = mTexture->Index;
	}
	
  static const GLubyte indices[4] = {0, 1, 2, 3};
  glVertexPointer(2, GL_INT, 0, vertices.Points);
  glTexCoordPointer(2, GL_FLOAT, 0, this->mTexCoords.Points);
  glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, indices);
}

Vec2< int > Image::getSize()
{
	return mSize;
}

