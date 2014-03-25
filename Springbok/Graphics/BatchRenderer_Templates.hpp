//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "BatchRenderer.h"
#include "GLES2.h"
#include "RenderContext2D.h"

template<class E, class V>
BatchRenderer<E,V>::BatchRenderer(int bytes) // Bytes is 2 MB by default
{
	mMaxVertices = bytes / sizeof(V);
	if(mMaxVertices > 65535) // With short indices we can't have more than 65k Vertices!
		mMaxVertices = 65535;
	
	mMaxElements = mMaxVertices / 16; // In the case of 2MB Vertices = Up to 4096 batches,    48 kB
	mMaxIndices  = mMaxVertices *  2; // In the case of 2MB Vertices = Up to 131072 indices, 256 kB
	
	mExtraVertices = 128;
	
	mVertexData  = new V       [mMaxVertices + mExtraVertices]; // 2MB = 65536 of the default vertices (32 bytes per Vertex)
	mElementData = new E       [mMaxElements + 2]; 
	mIndexData   = new GLushort[mMaxIndices  + mExtraVertices*2]; 
	
	glGenBuffers(1, &mVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, mMaxVertices * sizeof(V), NULL, GL_DYNAMIC_DRAW); 
	
	glGenBuffers(1, &mIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mMaxIndices * sizeof(GLushort), NULL, GL_DYNAMIC_DRAW); 
};

template<class E, class V>
template<typename T, typename... Args>
void BatchRenderer<E,V>::addToBatch(const T& object, Transform2D transformation, Args... args)
{	
	RenderDataPointer<V, E> oldParams = mParams;
	
	mParams.DefaultElement = DefaultElement;
	mParams.DefaultVertex  = DefaultVertex;
	mParams.updateDefaults();
	
	// Get the data before it is changed by prepareVertices.
	V* oldVertices = mVertexData + mParams.AddedVertices;
	
	object.prepareVertices(mParams, args...);
	
	if(mParams.AddedVertices > mMaxVertices)
	{
		Debug::Write("BatchRenderer: Wrote more vertices than we could handle. Flushing all batches and restarting.");
		// Rewind, flush, and press play again
		mParams = oldParams;
		flushBatches();
		addToBatch<T, Args...>(object, transformation, args...);
	}
	else
	{
		transformation.transform(oldVertices,
														mParams.Vertices,
														mCurrentContext->CameraPos,
														Vec2F(1, -1) / (mCurrentContext->renderTarget()->size()/2));
	}
};

template<class E, class V>
void BatchRenderer<E,V>::flushBatches()
{
	glBindBuffer(GL_ARRAY_BUFFER,         mVertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,  mIndexBuffer);
	
	glBufferSubData(GL_ARRAY_BUFFER,         0, Min(mParams.AddedVertices, mMaxVertices) * sizeof(V), mVertexData);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, Min(mParams.AddedIndices, mMaxIndices) * sizeof(GLushort), mIndexData);
	
	V::SetupOffsets();
	E::SetupUniforms(&mCurrentContext->shader());
	
	PrintGLError();
	E* last = (mElementData + Min(mParams.AddedElements, mMaxElements));
	for(E* it = mElementData; it < last; ++it)
	{
		it->bindUniforms();
		GLushort numIndices = (it->IndexEnd - it->IndexStart) - 1;
		glDrawElements(GL_TRIANGLE_STRIP, numIndices, GL_UNSIGNED_SHORT, (const void*)((it->IndexStart - mIndexData)*sizeof(GLushort)));
	}
	PrintGLError();
	
	mParams = RenderDataPointer<V, E>(mVertexData, mElementData, mIndexData);
};

template<class E, class V>
void BatchRenderer<E,V>::startBatching(const RenderContext2D& context)
{
	mCurrentContext = &context;
	DefaultVertex = V();
	DefaultElement = E();
	mParams = RenderDataPointer<V, E>(mVertexData, mElementData, mIndexData);
};