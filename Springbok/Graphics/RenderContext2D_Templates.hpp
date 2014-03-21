//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "RenderContext2D.h"
#include "GLES2.h"

template<typename T, typename... Args, class U, class V>
void RenderContext2D::draw(const T& object, Transform2D transformation, Args... args, const V& vinit, const U& uinit)
{
	static V       vertexData[1024];
	static U      elementData[ 256];
	static GLushort indexData[2048];
	
	RenderDataPointer<V, U> param(vertexData, elementData, indexData);
	param.DefaultElement = uinit;
	param.DefaultVertex  = vinit;
	
	object.prepareVertices(param, args...);
	
	Vec2F actualCameraPos = CameraPos - CameraAlignment * mRenderTarget->size();
	for(int i = 0; i < param.AddedElements; ++i)
	{
		transformation.transform(vertexData, elementData[i].IndexStart, elementData[i].IndexEnd, actualCameraPos, Vec2F(1) / mRenderTarget->size());
		
		elementData[i].bindUniforms();
		PrintGLError();
		
		GLushort numIndices = elementData[i].IndexEnd - elementData[i].IndexStart;
		vertexData->bindOffsets();
		PrintGLError();
		
		glDrawElements(GL_TRIANGLE_STRIP, numIndices, GL_UNSIGNED_SHORT, elementData[i].IndexStart);
		PrintGLError();
	};
};