// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <string>

#include "Core/VertexStruct.h"
#include "Core/Texture.h"

#include <Springbok/Geometry/Rect.h>
#include <Springbok/Generic/ObjectPointer.h>

struct Image
{
public:
	ObjectPointer<Texture> Data = nullptr;
	std::string Path;
	RectF TexCoords = RectF(0.0, 0.0, 1.f, 1.f);
public:
	Image(const std::string& filename);
	Image(const Image& other, Vec2I position, Vec2I size);
	Image(){};
	Vec2<int> size();
	Vec2<int> size() const;
	bool valid() const;
	Image cut(Vec2I position, Vec2I size);
	
	template<class V = BasicVertex, class E = BasicElement>
	void prepareVertices(RenderDataPointer< V, E >& data) const;
private:
	void lazyLoad();
	Vec2<int> mOffset = Vec2<int>(0, 0);
	Vec2<int> mSize = Vec2<int>(0, 0);
};

template<class V, class E>
void Image::prepareVertices(RenderDataPointer<V, E>& data) const
{
	RectF vertexCoords(0, mSize);
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