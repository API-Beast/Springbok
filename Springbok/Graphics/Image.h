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

class Image
{
public:
	Image(const std::string& filename);
	Image(const Image& other, Vec2I position, Vec2I size);
	Image(){};
	Vec2<int> size();
	Vec2<int> size() const;
	ObjectPointer<Texture> texture() const{ return mTexture; };
	bool valid() const;
	Image cut(Vec2I position, Vec2I size);
	
	template<class V = BasicVertex, class E = BasicElement>
	void prepareVertices(RenderDataPointer< V, E >& data) const;
private:
	void lazyLoad();
	ObjectPointer<Texture> mTexture = nullptr;
	std::string mPath;
	RectF mTexCoords = RectF(0.0, 0.0, 1.f, 1.f);
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
		data.Vertices->TexCoords = mTexCoords.Points[i];
		data.appendVertex();
	}
	data.appendIndex(0);
	data.appendIndex(1);
	data.appendIndex(2);
	data.appendIndex(3);
	
	E element = data.DefaultElement;
	element.Texture = mTexture->Index;
	data.appendElement(element);
}