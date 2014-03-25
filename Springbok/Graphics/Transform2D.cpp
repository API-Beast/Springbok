//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include "Transform2D.h"

Transform2D::Transform2D(Vec2I pos, Angle rotation, Vec2F scale, Vec2F alignment, Vec2F parallaxity)
{
	Offset = pos;
	Rotation = rotation;
	Scale = scale;
	Alignment = alignment;
	Parallaxity = parallaxity;
}

Transform2D::Transform2D(Vec2I pos, Vec2F scale, Vec2F alignment, Vec2F parallaxity)
{
	Offset = pos;
	Scale = scale;
	Alignment = alignment;
	Parallaxity = parallaxity;
}

Transform2D Transform2D::operator+(const Transform2D& other) const
{
	return Transform2D(this->Offset + other.Offset, this->Rotation + other.Rotation, this->Scale * other.Scale, 0.5f + (this->Alignment-0.5f) + (other.Alignment-0.5f), this->Parallaxity * other.Parallaxity);
}

Transform2D Transform2D::operator-(const Transform2D& other) const
{
	return Transform2D(this->Offset - other.Offset, this->Rotation - other.Rotation, this->Scale / other.Scale, 0.5f - (this->Alignment-0.5f) - (other.Alignment-0.5f), this->Parallaxity / other.Parallaxity);
}