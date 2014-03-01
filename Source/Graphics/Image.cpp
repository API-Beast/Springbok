// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#include "Image.h"
#include "Texture.h"
#include <Springbok/Resources/ResourceManager.h>
#include <Springbok/Utils/Debug.h>
#include "RenderContext.h"
#include "Camera.h"
#include <GL/glew.h>
#include <iostream>

Image::Image(const std::string& filename)
{
	mPath = filename;
	//lazyLoad();
}

Image::Image(const Image& other, Vec2I position, Vec2I size)
{
	mTexture = other.mTexture;
	mPath = other.mPath;
	mOffset = other.mOffset + position;
	mSize = size.upperBound(other.mSize - position);
	
	mTexCoords = mTexture->calcTextureCoordinates(mOffset, mSize);
}

RectF Image::getVertices()
{
	lazyLoad();
	return RectF(0,0,mSize.X,mSize.Y);
}

void Image::draw(RenderContext& r)
{
	lazyLoad();

	if(r.LastBoundTexture != mTexture->Index)
	{
		glBindTexture(GL_TEXTURE_2D, mTexture->Index);
		r.LastBoundTexture = mTexture->Index;
	}

	r.draw(vertexBuffer,textureBuffer);
	/*
	RectF vertices = r.getTransformedRect<float>(Vec2F(0, 0), mSize);
	
	if(r.LastBoundTexture != mTexture->Index)
	{
		glBindTexture(GL_TEXTURE_2D, mTexture->Index);
		r.LastBoundTexture = mTexture->Index;
	}
	
	static const GLubyte indices[4] = {0, 1, 2, 3};
	glVertexPointer(2, GL_FLOAT, 0, vertices.Points);
	glTexCoordPointer(2, GL_FLOAT, 0, this->mTexCoords.Points);
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, indices);*/
}

void Image::drawStretched(Vec2< int > size, const RenderContext& r)
{
	lazyLoad();
	
	RectF vertices = r.getTransformedRect<float>(Vec2F(0, 0), size);
	
	if(r.LastBoundTexture != mTexture->Index)
	{
		glBindTexture(GL_TEXTURE_2D, mTexture->Index);
		r.LastBoundTexture = mTexture->Index;
	}
	
	static const GLubyte indices[4] = {0, 1, 2, 3};
	glVertexPointer(2, GL_FLOAT, 0, vertices.Points);
	glTexCoordPointer(2, GL_FLOAT, 0, this->mTexCoords.Points);
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, indices);
}

void Image::drawRepeated(const RenderContext& r)
{
	drawRepeated(r, r.RenderTargetOrigin, r.RenderTargetSize);
}

void Image::drawRepeated(const RenderContext& context, Vec2F clippingPos, Vec2F clippingSize)
{
	// I could really use a Grid class similar to the Rect class :)
	// Grid g(mSize);
	// context.transform(g);
	// g.clipTo(clippingPos, clippingSize);
	// or something.
	RenderContext r(context);
	r.CameraPos = 0;
	r.Alignment = 0;
	r.Parallaxity = 0;
	Vec2I size = mSize * Abs(r.Scale);
	Vec2F startPos = (clippingPos - size + (Vec2I(context.Offset-(context.CameraPos*context.Parallaxity))%size));
	Vec2F endPos = (clippingPos + clippingSize + size);
	Vec2F curPos = startPos;
	while(curPos.Y < endPos.Y)
	{
		curPos.X = startPos.X;
		while(curPos.X < endPos.X)
		{
			r.Offset = curPos;
			draw(r);
			RectF simRect = r.getTransformedRect<float>(Vec2F(0, 0), mSize);
			curPos.X = simRect.Bottom.Right.X;
		}
		RectF simRect = r.getTransformedRect<float>(Vec2F(0, 0), mSize);
		curPos.Y = simRect.Bottom.Right.Y;
	}
}

Image Image::cut(Vec2I position, Vec2I size)
{
	return Image(*this, position, size);
}

Vec2< int > Image::getSize()
{	
	lazyLoad();
	return mSize;
}

Vec2< int > Image::getSize() const
{	
	return mSize;
}

bool Image::valid() const
{
	return mTexture && mTexture->Valid;
}

void Image::generateVertices(const RenderContext& r)
{
}

ObjectPointer<Texture> Image::getTexture()
{
	lazyLoad();
	return mTexture;
}

void Image::lazyLoad()
{
	if(mTexture != nullptr)
		if(mTexture->Valid)
			return ;
		
	mTexture = ResourceManager::GetInstance()->getResource<Texture>(mPath);
	if(mTexture->Valid == false) {
		Debug::Write("WARNING: Texture is not valid!");
		return;
	}

	mSize = mTexture->ImageSize;
	mTexCoords = mTexture->TextureCoordinates;
}
