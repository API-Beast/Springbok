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
	Path = filename;
	lazyLoad();
}

void Image::lazyLoad()
{
	if(Data != nullptr)
		if(Data->Valid)
			return ;

	Data = ResourceManager::GetInstance()->getResource<Texture>(Path);
	if(Data->Valid == false)
		return;

	TexCoords = Data->TextureCoordinates;
	mSize     = Data->ImageSize;
}

Image::Image(const Image& other, Vec2I position, Vec2I size)
{
	Data = other.Data;
	Path = other.Path;
	mOffset = other.mOffset + position;
	mSize = size.upperBound(other.mSize - position);

	TexCoords = Data->calcTextureCoordinates(mOffset, mSize);
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

void Image::setAlign(Vec2F align)
{
	mAlignment = align;
}

void Image::setCenter(Vec2I pos)
{
	mAlignment = pos / Vec2F(mSize);
}

Vec2I Image::center() const
{
	return mSize * mAlignment;
}

Vec2F Image::alignment() const
{
	return mAlignment;
}

bool Image::valid() const
{
	return Data && Data->Valid;
}

Vec2I Image::offset() const
{
	return mOffset;
}