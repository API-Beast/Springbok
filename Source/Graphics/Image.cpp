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

void Image::drawStretched(Vec2< int > size, const RenderContext& r)
{
	lazyLoad();
	
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
		if(!errorReported) {
			Debug::Write("WARNING: Texture is not valid!");
			errorReported = true;
		}
		return;
	}

	mSize = mTexture->ImageSize;
	mTexCoords = mTexture->TextureCoordinates;
}
