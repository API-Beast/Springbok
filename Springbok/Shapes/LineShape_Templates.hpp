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
		int x = BoundBy(1, i, Points.UsedLength-2);

		Point pPrev = Points[x-1];
		Point pTang = Points[x  ];
		Point pNext = Points[x+1];
		
		Vec2F  inTangent = pPrev.Position - pTang.Position;
		Vec2F outTangent = pTang.Position - pNext.Position;
		
		tangent = (inTangent + outTangent) / 2;
		if(tangent.isNull())
			tangent = Vec2F(1, 0);
		
		Vec2F side = tangent.rot90().normalized();
		
		Point curPoint = Points[i];
		
		data.Vertices->Position  = curPoint.Position + (curPoint.Width/2) *  side;
		data.Vertices->TexCoords = texStart + Vec2F(curPoint.TexCoord, 0) * texSize;
		data.Vertices->Color     = curPoint.Color;
		data.appendVertex();
		
		data.Vertices->Position  = curPoint.Position + (curPoint.Width/2) * -side;
		data.Vertices->TexCoords = texStart + Vec2F(curPoint.TexCoord, 1) * texSize;
		data.Vertices->Color     = curPoint.Color;
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