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
	constexpr int vertices = 2097152 / sizeof(V);
	mVertexData  = new V       [vertices *  1]; // 2MB = 65536 of the default vertices (32 bytes per Vertex)
	mElementData = new E       [vertices / 16]; // 2MB Vertices = Up to 4096 batches,    48 kB
	mIndexData   = new GLushort[vertices *  2]; // 2MB Vertices = Up to 131072 indices, 256 kB
	
	glGenBuffers(1, &mVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices * sizeof(V), NULL, GL_DYNAMIC_DRAW); 
	
	glGenBuffers(1, &mIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertices * 2 * sizeof(GLushort), NULL, GL_DYNAMIC_DRAW); 
};

template<class E, class V>
template<typename T, typename... Args>
void BatchRenderer<E,V>::addToBatch(const T& object, Transform2D transformation, Args... args)
{
	E* current = mElementData + mParams.AddedElements - 1;
	V* oldVertices = mVertexData + mParams.AddedVertices;
	
	mParams.DefaultElement = DefaultElement;
	mParams.DefaultVertex  = DefaultVertex;
	
	object.prepareVertices(mParams, args...);
	
	// Merge adjacent elements for batching
	
	E* oldEnd  = mElementData + mParams.AddedElements;
	// TODO
  /*E* newEnd  = current;
  while(++current != oldEnd)
	{
    if((*newEnd == *current))
		{
			newEnd++;
      newEnd->IndexEnd = current->IndexEnd;
		}
	}*/
	E* newEnd = oldEnd;
		
	transformation.transform(oldVertices,
													 mParams.Vertices,
													 mCurrentContext->CameraPos,
													 Vec2F(1, -1) / (mCurrentContext->renderTarget()->size()/2));
	
	mParams.AddedElements = (newEnd - mElementData);
};

template<class E, class V>
void BatchRenderer<E,V>::flushBatches()
{
	glBindBuffer(GL_ARRAY_BUFFER,         mVertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,  mIndexBuffer);
	
	glBufferSubData(GL_ARRAY_BUFFER,         0, mParams.AddedVertices * sizeof(V),        mVertexData);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, mParams.AddedIndices  * sizeof(GLushort), mIndexData);
	
	V::SetupOffsets();
	E::SetupUniforms(&mCurrentContext->shader());
	
	PrintGLError();
	for(E* it = mElementData; it < (mElementData + mParams.AddedElements); ++it)
	{
		it->bindUniforms();
		GLushort numIndices = (it->IndexEnd - it->IndexStart) - 1;
		glDrawElements(GL_TRIANGLE_STRIP, numIndices, GL_UNSIGNED_SHORT, (const void*)((it->IndexStart - mIndexData)*sizeof(GLushort)));
	}
	PrintGLError();
	mParams = RenderDataPointer<V, E>(mVertexData, mElementData, mIndexData);
};