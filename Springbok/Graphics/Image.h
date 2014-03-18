// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <string>

#include <Springbok/Geometry/Rect.h>
#include <Springbok/Generic/ObjectPointer.h>
#include "VertexArray.h"
#include "Texture.h"

class RenderContext;

class Texture;


class Image
{
public:
	Image(const std::string& filename);
	Image(const Image& other, Vec2I position, Vec2I size);
	Image(){};
	Vec2<int> getSize();
	Vec2<int> getSize() const;
	bool valid() const;
	Image cut(Vec2I position, Vec2I size);
	
	template<class V = BasicVertex, class U = BasicElement>
	int prepareVertices(V*& vertices, U*& properties) const;
private:
	void lazyLoad();
	ObjectPointer<Texture> mTexture = nullptr;
	std::string mPath;
	RectF mTexCoords = RectF(0.0, 0.0, 1.f, 1.f);
	Vec2<int> mOffset = Vec2<int>(0, 0);
	Vec2<int> mSize = Vec2<int>(0, 0);
};

template<class V, class U>
int Image::prepareVertices(V*& vertices, U*& properties) const
{
	RectF vertexCoords(0, mSize);
	for(int i = 0; i < 4; ++i)
	{
		vertices->Position  = vertexCoords.Points[i];
		vertices->TexCoords = mTexCoords.Points[i];
		vertices++;
	}
	properties->Texture = mTexture->Index;
	properties->Vertices = 4;
	properties++;
	return 1;
}