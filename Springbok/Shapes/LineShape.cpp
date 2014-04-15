//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include "LineShape.h"
#include "../Animation/Interpolation.h"

void LineShape::insert(Vec2F position, float width, Vec4F color)
{
	Point p;
	p.Position = position;
	p.Width    = width;
	p.Color    = color;
	Points.pushBack(p);
}

float LineShape::calcLength()
{
	float length = 0;
	for(int i = 1; i < Points.UsedLength; ++i)
		length += (Points[i].Position - Points[i-1].Position).length();
	return length;
}

void LineShape::divideEquidistant(float pixels)
{
	List<Point> newPoints;
	
	for(int i = 1; i < Points.UsedLength; ++i)
	{
		Point p1 = Points[i-1];
		Point p2 = Points[i];
		Point p3 = p2;
		Point p0 = p1;
		
		if(i >= 2)                    p0 = Points[i-2];
		if(i < Points.UsedLength - 1) p3 = Points[i+1];
		
		float length = (p1.Position - p2.Position).length();
		int segments = 1 + length / pixels;
		
		newPoints.pushBack(p1);
		for(int j = 1; j < segments; ++j)
		{
			float factor = 1.f / segments * j;
			Point newP;
			newP.Position = InterpolateCubic(p0.Position, p1.Position, p2.Position, p3.Position, factor);
			newP.   Width = InterpolateCubic(p0.Width   , p1.Width   , p2.Width   , p3.Width   , factor);
			newP.TexCoord = InterpolateCubic(p0.TexCoord, p1.TexCoord, p2.TexCoord, p3.TexCoord, factor);
			newP.   Color = InterpolateCubic(p0.Color   , p1.Color   , p2.Color   , p3.Color   , factor);
			newPoints.pushBack(newP);
		}
		newPoints.pushBack(p2);
	}
	Points = newPoints;
}

void LineShape::applyTexture(const Image& img, float repetitions)
{
	TexImage = img;
	float length = 0;
	float maxLength = calcLength();
	Points[0].TexCoord = 0;
	for(int i = 1; i < Points.UsedLength; ++i)
	{
		length += (Points[i].Position - Points[i-1].Position).length();
		Points[i].TexCoord = (length / maxLength) * repetitions;
	}
}
