//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "LineShape.h"

template<class V, class E>
void LineShape::prepareVertices(RenderDataPointer< V, E >& data) const
{
	Vec2F texStart = TexImage.TexCoords.Top.Left;
	Vec2F texSize  = TexImage.TexCoords.Bottom.Right - TexImage.TexCoords.Top.Left;
	for(int i = 0; i < Points.UsedLength; ++i)
	{
		Vec2F tangent;
		Point pFirs = Points[i-1];
		Point pCurr = Points[i  ];
		Point pNext = Points[i+1];
		
		Vec2F  inTangent = pFirs.Position - pCurr.Position;
		Vec2F outTangent = pCurr.Position - pNext.Position;
		
		// pNext was invalid
		if(i > (Points.UsedLength-1)) outTangent = inTangent; 
		// pFirs was invalid
		if(i < 1) inTangent = outTangent;
		// Will be garbage if both were invalid, but that would imply it was a curve with a single point which won't be visible anyway.
		tangent = (inTangent + outTangent) / 2;
		
		Vec2F side = tangent.rot90().normalized();
		
		data.Vertices->Position  = pCurr.Position + (pCurr.Width/2) *  side;
		data.Vertices->TexCoords = texStart + Vec2F(pCurr.TexCoord, 0) * texSize;
		data.Vertices->Color     = pCurr.Color;
		data.appendVertex();
		
		data.Vertices->Position  = pCurr.Position + (pCurr.Width/2) * -side;
		data.Vertices->TexCoords = texStart + Vec2F(pCurr.TexCoord, 1) * texSize;
		data.Vertices->Color     = pCurr.Color;
		data.appendVertex();
		
		data.appendIndex(i*2);
		data.appendIndex(i*2+1);
	}
	
	E element = data.DefaultElement;
	if(TexImage.valid())
		element.Texture = TexImage.Data->Index;
	else
		element.Texture = 0;
	data.appendElement(element);
}