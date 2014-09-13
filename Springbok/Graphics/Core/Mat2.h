//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <Springbok/Foundation/Vec2.h>

struct Mat2
{
	Vec2F Rows[2];
	
	constexpr Mat2(Vec2F r0, Vec2F r1) : Rows({r0, r1}){};
	      Vec2F& operator[](int index)      { return Rows[index]; };
	const Vec2F& operator[](int index) const{ return Rows[index]; };
	
	Vec2F transform(Vec2F value) const
	{
		return {(value * Rows[0]).sum(), (value * Rows[1]).sum()};
	};
	Mat2 mult(Mat2 other) const
	{
		Vec2F Collums[2];
		Collums[0] = Vec2F(other.Rows[0][0], other.Rows[1][0]);
		Collums[1] = Vec2F(other.Rows[0][1], other.Rows[1][1]);
		return {{Rows[0].dot(Collums[0]), Rows[0].dot(Collums[1])},
			      {Rows[1].dot(Collums[0]), Rows[1].dot(Collums[1])}};
	};
	
	static constexpr Mat2 Identity(){ return Mat2(Vec2F(1, 0), Vec2F(0, 1)); }; 
};

#define def_operator(OPER)\
	inline Mat2 operator OPER (const Mat2& v0, const Mat2& v1){ return {v0[0] OPER v1[0], v0[1] OPER v1[1]}; };\
	inline Mat2 operator OPER (const Mat2& v0, float val){ return {v0[0] OPER val, v0[1] OPER val}; }\
	inline Mat2 operator OPER (float val, const Mat2& v0){ return {v0[0] OPER val, v0[1] OPER val}; }
def_operator(+);
def_operator(-);
def_operator(/);
def_operator(*);
#undef def_operator

#define def_assign_operator(OPER)\
	inline Mat2& operator OPER(Mat2& v0, const Mat2& v1){ v0[0] OPER v1[0]; v0[1] OPER v1[1]; return v0; }
def_assign_operator(+=);
def_assign_operator(-=);
def_assign_operator(*=);
def_assign_operator(/=);
#undef def_assign_operator