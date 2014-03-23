//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <Springbok/Geometry/Vec4.h>
#include "Color.h"
#include "GLES2.h"

struct BasicVertex;
struct BasicElement;
struct ShaderProgram;

struct BasicVertex
{
	Vec2F Position  = 0.f;
	Vec2F TexCoords = 0.f;
	Vec4F Color     = Colors::White;
	
	static void SetupOffsets();
};

struct BasicElement
{
	int Texture = 0;
	GLushort* IndexStart;
	GLushort* IndexEnd;
	
	static void SetupUniforms(const ShaderProgram* shader);
	
	void bindUniforms() const;
	void bindUniforms(const BasicElement& previous) const;
	bool operator==(BasicElement& other){ return other.Texture == Texture; };
};

template<class V = BasicVertex, class E = BasicElement>
struct RenderDataPointer
{	
	V* Vertices;
	E* Elements;
	GLushort* Indices;
	
	V DefaultVertex  = V();
	E DefaultElement = E();
	GLushort CurrentIndex = 0;
	
	int AddedVertices = 0;
	int AddedVerticesToCurElement = 0;
	int AddedElements = 0;
	int AddedIndices  = 0;
	
	bool NewElement = false;
	
	RenderDataPointer() = default;
	RenderDataPointer(V* vertices, E* elements, GLushort* indices)
	{
		Vertices = vertices;
		Elements = elements;
		Indices  = indices;
		
		(*Vertices) = DefaultVertex;
		(*Elements) = DefaultElement;
		Elements->IndexStart = Indices;
	};
	
	void appendVertex()
	{
		Vertices++;
		AddedVertices++;
		AddedVerticesToCurElement++;
		(*Vertices) = DefaultVertex;
	};
	void appendIndex(GLushort index)
	{
		// Add degenerate indizes 
		if(NewElement)
		{
			Indices[0] = Indices[-1];
			Indices[1] = index + CurrentIndex;
			NewElement = false;
			Indices += 2;
			AddedIndices += 2;
			Elements->IndexStart += 2;
		}
		Indices[0] = index + CurrentIndex;
		Indices++;
		AddedIndices++;
	};
	void appendElement()
	{
		Elements->IndexEnd = Indices + 1;
		Elements++;
		AddedElements++;
		(*Elements) = DefaultElement;
		NewElement = true;
		Elements->IndexStart = Indices;
		CurrentIndex += AddedVerticesToCurElement;
		AddedVerticesToCurElement = 0;
	};
};