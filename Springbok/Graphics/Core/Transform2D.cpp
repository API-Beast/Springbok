//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include "Transform2D.h"

Transform2D::Transform2D(Mat2 matrix) : Matrix(matrix)
{
}

Transform2D::Transform2D(Vec2I pos, Vec2F parallaxity, Mat2 matrix):
	Offset(pos), Parallaxity(parallaxity), Matrix(matrix)
{
}

Transform2D Transform2D::operator+(const Transform2D& other) const
{
	return Transform2D(this->Offset + other.Offset, this->Parallaxity * other.Parallaxity, Matrix.mult(other.Matrix));
}

Transform2D Transform2D::operator-(const Transform2D& other) const
{
	return Transform2D(this->Offset - other.Offset, this->Parallaxity / other.Parallaxity, Matrix.mult(1/other.Matrix));
}

Transform2D& Transform2D::operator+=(const Transform2D& other)
{
	Offset      += other.Offset;
	Parallaxity *= other.Parallaxity;
	Matrix = Matrix.mult(other.Matrix);
	return *this;
}

Transform2D& Transform2D::operator-=(const Transform2D& other)
{
	Offset      -= other.Offset;
	Parallaxity /= other.Parallaxity;
	Matrix = Matrix.mult(1/other.Matrix);
	return *this;
}

Transform2D Transform2D::inverse() const
{
	return Transform2D() - *this;
}

Vec2F Transform2D::transformVec2(Vec2F v, Vec2F cameraPos, Vec2F size) const
{
	return Matrix.transform(v) + Offset - cameraPos * Parallaxity;
}
