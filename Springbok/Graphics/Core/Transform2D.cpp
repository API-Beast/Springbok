//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include "Transform2D.h"

Transform2D::Transform2D(Mat2 matrix) : Matrix(matrix)
{
}

Transform2D::Transform2D(Vec2I pos, Vec2F alignment, Vec2F parallaxity, Mat2 matrix):
	Offset(pos), Alignment(alignment), Parallaxity(parallaxity), Matrix(matrix)
{
}

Transform2D Transform2D::operator+(const Transform2D& other) const
{
	return Transform2D(this->Offset + other.Offset, 0.5f + (this->Alignment-0.5f) + (other.Alignment-0.5f), this->Parallaxity * other.Parallaxity, Matrix.mult(other.Matrix));
}

Transform2D Transform2D::operator-(const Transform2D& other) const
{
	return Transform2D(this->Offset - other.Offset, 0.5f - (this->Alignment-0.5f) - (other.Alignment-0.5f), this->Parallaxity / other.Parallaxity, Matrix.mult(1/other.Matrix));
}

Transform2D& Transform2D::operator+=(const Transform2D& other)
{
	Offset      += other.Offset;
	Alignment    = 0.5f + (Alignment-0.5f) + (other.Alignment-0.5f);
	Parallaxity *= other.Parallaxity;
	Matrix = Matrix.mult(other.Matrix);
	return *this;
}

Transform2D& Transform2D::operator-=(const Transform2D& other)
{
	Offset      -= other.Offset;
	Alignment    = 0.5f - (Alignment-0.5f) - (other.Alignment-0.5f);
	Parallaxity /= other.Parallaxity;
	Matrix = Matrix.mult(1/other.Matrix);
	return *this;
}

Transform2D Transform2D::xOnly() const
{
	Mat2 mat = Matrix;
	mat.Rows[1] = Vec2F(0, 1);
	return Transform2D({this->Offset.X, 0.f}, {this->Alignment.X, 0.5f}, {this->Parallaxity.X, 1.0f}, mat);
}

Transform2D Transform2D::yOnly() const
{
	Mat2 mat = Matrix;
	mat.Rows[0] = Vec2F(1, 0);
	return Transform2D({0.f, this->Offset.Y}, {0.5f, this->Alignment.Y}, {1.0f, this->Parallaxity.Y}, mat);
}

Transform2D Transform2D::inverse() const
{
	return Transform2D() - *this;
}

Vec2F Transform2D::transformVec2(Vec2F v, Vec2F cameraPos, Vec2F size) const
{
	return Matrix.transform(v - size*Alignment) + Offset - cameraPos * Parallaxity;
}
