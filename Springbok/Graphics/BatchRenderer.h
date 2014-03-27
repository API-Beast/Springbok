//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "VertexStruct.h"
#include "Transform2D.h"

class RenderContext2D;

template<class E = BasicElement, class V = BasicVertex>
class BatchRenderer
{
public:
public:
	BatchRenderer(int bytes = 1048576);
	void startBatching(const RenderContext2D& context);
	template<typename T, typename... Args>
	void addToBatch(const T& object, Transform2D transformation = Transform2D(), const V& vertex = V(), const E& element = E());
	void flushBatches();
private:
	const RenderContext2D* mCurrentContext = nullptr;
	
	BasicVertex*  mVertexData  = nullptr;
	BasicElement* mElementData = nullptr;
	GLushort*     mIndexData   = nullptr;
	
	GLuint mVertexBuffer = 0;
	GLuint mIndexBuffer  = 0;
	
	int mMaxVertices = 0;
	int mMaxElements = 0;
	int mMaxIndices  = 0;
	
	int mExtraVertices = 0;
	
	bool mGLStateIsSet = false;
	
	RenderDataPointer<V, E> mParams;
};

using BatchRenderer2D = BatchRenderer<>;

#include "BatchRenderer_Templates.hpp"

