//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include "LineShape.h"
#include <Springbok/Utils/Functions.h>

LineShape LineShape::Arrow(Vec2F vec, float width, Vec4F endClr, Vec4F startClr)
{
	LineShape retVal;
	retVal.insert(0, width, startClr);
	retVal.insert(vec, width, endClr);
	retVal.divideSmooth(5);
	return retVal;
}

LineShape LineShape::Arrow(Vec2F vec, const Image& arrowImg, Vec4F clr, float width)
{
	if(width == -1.f)
		width = arrowImg.size().Y;
	LineShape retVal;
	retVal.insert(0, width, clr);
	retVal.insert(vec, width, clr);
	retVal.divideSmooth(5);
	retVal.applyTexture(arrowImg);
	return retVal;
}

LineShape LineShape::Arrow(Vec2F vec, LineStyle style, Vec4F clr, float width)
{
	if(width == -1.f)
		width = style.TexImage.size().Y;
	LineShape retVal;
	retVal.insert(0, width, clr);
	retVal.insert(vec, width, clr);
	retVal.divideSmooth(5);
	retVal.applyStyle(style);
	return retVal;
}

LineShape LineShape::TurnIndicator(Angle turns, float radius, LineStyle style, Vec4F clr, float width)
{
	if(width == -1.f)
		width = style.TexImage.size().Y;
	
	LineShape retVal;
	turns = -turns;
	for(Angle a = 0_turn; true; a = Approach(a, turns, 5_deg))
	{
		retVal.insert(a.toDirection()*radius, width, clr);
		if(a == turns)
			break;
	}
	//retVal.divideEquidistant(5);
	retVal.applyStyle(style);
	return retVal;
}


void LineShape::insert(Vec2F position, float width, Vec4F color)
{
	Point p;
	p.Position = position;
	p.Width    = width;
	p.Color    = color;
	Points.push_back(p);
}

float LineShape::calcLength()
{
	float length = 0;
	for(int i = 1; i < Points.size(); ++i)
		length += (Points[i].Position - Points[i-1].Position).length();
	return length;
}

void LineShape::divideLinear(float pixels, int maxSegments)
{
	std::vector<Point> newPoints;
	
	for(int i = 1; i < Points.size(); ++i)
	{
		Point p0, p1;
		p0 = Points[i-1];
		p1 = Points[i];
		
		float length = (p0.Position - p1.Position).length();
		int segments = 1 + length / pixels;

		if((segments > maxSegments) && (maxSegments != -1))
			segments = maxSegments;
		
		newPoints.push_back(p0);
		for(int j = 1; j < segments; ++j)
		{
			float factor = 1.f / segments * j;
			Point newP = p0.blend(p1, factor);
			newPoints.push_back(newP);
		}
		newPoints.push_back(p1);
	}
	Points = newPoints;
}

void LineShape::divideSmooth(float pixels, int maxSegments)
{
	std::vector<Point> newPoints;
	
	for(int i = 1; i < Points.size(); ++i)
	{
		Point p0, p1, p2, p3;
		p1 = Points[i-1];
		p2 = Points[i];
		p0 = (i >= 2 ?
		      Points[i-2] : p1);
		p3 = (i < Points.size() - 1 ?
		      Points[i+1] : p1);
		
		float length = (p1.Position - p2.Position).length();
		int segments = 1 + length / pixels;

		if((segments > maxSegments) && (maxSegments != -1))
			segments = maxSegments;
		
		newPoints.push_back(p1);
		for(int j = 1; j < segments; ++j)
		{
			float factor = 1.f / segments * j;
			Point newP;
			newP.Position = InterpolateCubic(p0.Position, p1.Position, p2.Position, p3.Position, factor);
			newP.   Width = InterpolateCubic(p0.Width   , p1.Width   , p2.Width   , p3.Width   , factor);
			newP.TexCoord = InterpolateCubic(p0.TexCoord, p1.TexCoord, p2.TexCoord, p3.TexCoord, factor);
			newP.   Color = InterpolateCubic(p0.Color   , p1.Color   , p2.Color   , p3.Color   , factor);
			newPoints.push_back(newP);
		}
		newPoints.push_back(p2);
	}
	Points = newPoints;
}

LineShape::Point LineShape::Point::blend(const LineShape::Point& other, float factor)
{
	LineShape::Point retVal;
	float nFactor = 1.f - factor;
	retVal.Position = (this->Position * nFactor + other.Position * factor);
	retVal.Color    = (this->Color    * nFactor + other.Color    * factor);
	retVal.TexCoord = (this->TexCoord * nFactor + other.TexCoord * factor);
	retVal.Width    = (this->Width    * nFactor + other.Width    * factor);
	return retVal;
}

void LineShape::divideCubicBezier(float pixels)
{
	std::vector<Point> newPoints;
	
	for(int i = 1; i < Points.size(); i+=3)
	{
		Point p0, p1, p2, p3;
		p0 = Points[i-1];
		p1 = Points[i];
		p2 = (i < Points.size() - 1) ?
		      Points[i+1] : p1;
		p3 = (i < Points.size() - 2) ?
		      Points[i+2] : p2;
		
		float length = (p0.Position - p3.Position).length();
		int segments = 1 + length / pixels;
		
		for(int j = 1; j < segments; ++j)
		{
			float factor = 1.f / segments * j;
			Point qA = p0.blend(p1, factor);
			Point qB = p1.blend(p2, factor);
			Point qC = p2.blend(p3, factor);
			
			Point pA = qA.blend(qB, factor);
			Point pB = qB.blend(qC, factor);
			
			Point newP = pA.blend(pB, factor);
			newPoints.push_back(newP);
		}
		newPoints.push_back(p3);
	}
	Points = newPoints;
}

void LineShape::applyTexture(const Image& img, float repetitions)
{
	TexImage = img;
	float length = 0;
	float maxLength = calcLength();
	Points[0].TexCoord = 0;
	for(int i = 1; i < Points.size(); ++i)
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
	
	if(maxLength < style.StartLength + style.EndLength)
	{
		float startCoord = (texLength - maxLength) / texLength;
		Points[0].TexCoord = startCoord;
		for(int i = 1; i < Points.size(); ++i)
		{
			length += (Points[i].Position - Points[i-1].Position).length();
			Points[i].TexCoord = startCoord + length / texLength;
		}
	}
	else
	{
		float centerStart  = style.StartLength;
		float centerEnd    = maxLength - style.EndLength; 
		float centerLength = maxLength - centerStart - (maxLength - centerEnd);
		
		Points[0].TexCoord = 0;
		for(int i = 1; i < Points.size(); ++i)
		{
			length += (Points[i].Position - Points[i-1].Position).length();
			// Start
			if(length < centerStart)
				Points[i].TexCoord = normCenterStart * (length / style.StartLength);
			// End
			else if(length > centerEnd)
			{
				float endPos = (length - centerEnd) / style.EndLength;
				Points[i].TexCoord = normCenterEnd + (1.f - normCenterEnd)*endPos;
			}
			// Center
			else
			{
				float centerPos = (length - centerStart) / (maxLength - style.StartLength - style.EndLength);
				Points[i].TexCoord = normCenterStart + (normCenterEnd - normCenterStart) * centerPos;
			}
		}
	}
}

LineStyle::LineStyle(Image img, int start, int end)
{
	TexImage = img;
	CenterStartPx = start;
	CenterEndPx   = img.size().X - end;
	StartLength    = start;
	RepitionLength = img.size().X - start - end;
	EndLength      = end;
}
