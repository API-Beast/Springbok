// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#include "Image.h"

#include "Core/Texture.h"
#include "Core/RenderContext2D.h"

#include <Springbok/Resources/ResourceManager.h>

Image::Image(const std::string& filename)
{
	mPath = filename;
	lazyLoad();
}

void Image::lazyLoad()
{
	if(mTexture != nullptr)
		if(mTexture->Valid)
			return ;

	mTexture = ResourceManager::GetInstance()->getResource<Texture>(mPath);
	if(mTexture->Valid == false)
		return;

	mTexCoords = mTexture->TextureCoordinates;
	mSize = mTexture->ImageSize;
}

Image::Image(const Image& other, Vec2I position, Vec2I size)
{
	mTexture = other.mTexture;
	mPath = other.mPath;
	mOffset = other.mOffset + position;
	mSize = size.upperBound(other.mSize - position);

	mTexCoords = mTexture->calcTextureCoordinates(mOffset, mSize);
}

Image Image::cut(Vec2I position, Vec2I size)
{
	return Image(*this, position, size);
}

Vec2< int > Image::size()
{
	lazyLoad();
	return mSize;
}

Vec2< int > Image::size() const
{
	return mSize;
}

bool Image::valid() const
{
	return mTexture && mTexture->Valid;
}