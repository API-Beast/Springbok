// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <string>

#include "Core/VertexStruct.h"
#include "Core/Texture.h"

#include <Springbok/Types/Rect.h>
#include <Springbok/Types/ObjectPointer.h>

struct Image
{
public:
	ObjectPointer<Texture> Data = nullptr;
	std::string Path;
	Rect TexCoords = Rect(0.0, 0.0, 1.f, 1.f);
public:
	Image(const std::string& filename);
	Image(const Image& other, Vec2I position, Vec2I size);
	Image(){};
	Vec2I size();
	Vec2I offset() const;
	Vec2I size() const;
	Vec2I center() const;
	Vec2F alignment() const;
	void setCenter(Vec2I pos);
	void setAlign(Vec2F align);
	bool valid() const;
	Image cut(Vec2I position, Vec2I size);
	
	template<class V = BasicVertex, class E = BasicElement>
	void prepareVertices(RenderDataPointer< V, E >& data) const;
private:
	void lazyLoad();
	Vec2I mOffset    = Vec2I(0, 0);
	Vec2I mSize      = Vec2I(0, 0);
	Vec2F mAlignment = 0.5f;
};

template<class V, class E>
void Image::prepareVertices(RenderDataPointer<V, E>& data) const
{
	Rect vertexCoords(-center(), mSize);
	for(int i = 0; i < 4; ++i)
	{
		data.Vertices->Position  = vertexCoords.Points[i];
		data.Vertices->TexCoords = TexCoords.Points[i];
		data.appendVertex();
	}
	data.appendIndex(0);
	data.appendIndex(1);
	data.appendIndex(2);
	data.appendIndex(3);
	
	E element = data.DefaultElement;
	element.Texture = Data->Index;
	data.appendElement(element);
}