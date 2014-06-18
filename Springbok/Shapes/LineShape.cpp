//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include "LineShape.h"
#include "../Animation/Interpolation.h"

LineShape LineShape::Arrow(Vec2F vec, float width, ColorRGBA endClr, ColorRGBA startClr)
{
	LineShape retVal;
	retVal.insert(0, width, startClr);
	retVal.insert(vec, width, endClr);
	retVal.divideEquidistant(5);
	return retVal;
}

LineShape LineShape::Arrow(Vec2F vec, const Image& arrowImg, ColorRGBA clr, float width)
{
	if(width == -1.f)
		width = arrowImg.size().Y;
	LineShape retVal;
	retVal.insert(0, width, clr);
	retVal.insert(vec, width, clr);
	retVal.divideEquidistant(5);
	retVal.applyTexture(arrowImg);
	return retVal;
}

LineShape LineShape::Arrow(Vec2F vec, LineStyle style, ColorRGBA clr, float width)
{
	if(width == -1.f)
		width = style.TexImage.size().Y;
	LineShape retVal;
	retVal.insert(0, width, clr);
	retVal.insert(vec, width, clr);
	retVal.divideEquidistant(5);
	retVal.applyStyle(style);
	return retVal;
}

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

void LineShape::applyStyle(const LineStyle& style)
{
	TexImage = style.TexImage;
	
	float length = 0;
	float maxLength = calcLength();
	
	float texLength = style.TexImage.Data->TextureSize.X;
	float normCenterStart = style.CenterStartPx / texLength;
	float normCenterEnd   = style.CenterEndPx   / texLength;
	
	float centerStart  = style.StartLength;
	float centerEnd    = maxLength - style.EndLength; 
	float centerLength = maxLength - style.StartLength - style.EndLength;
	
	Points[0].TexCoord = 0;
	for(int i = 1; i < Points.UsedLength; ++i)
	{
		length += (Points[i].Position - Points[i-1].Position).length();
		// Start
		if(length < style.StartLength)
			Points[i].TexCoord = normCenterStart * (length / style.StartLength);
		// End
		else if(length > centerEnd)
		{
			float endPos = (length - centerEnd) / style.EndLength;
			Points[i].TexCoord = normCenterEnd + (1.f - normCenterEnd)*endPos;
		}
		// Center
		// TODO: Implement "Repeat" center mode
		else
		{
			float centerPos = (length - centerStart) / centerLength;
			Points[i].TexCoord = normCenterStart + (normCenterEnd - normCenterStart)*centerPos;
		}
	}
}

LineStyle::LineStyle(Image img, int start, int end)
{
	TexImage = img;
	CenterStartPx = start;
	CenterEndPx   = img.size().X - end;
	Mode = Stretch;
	StartLength    = start;
	RepitionLength = img.size().X - start - end;
	EndLength      = end;
}