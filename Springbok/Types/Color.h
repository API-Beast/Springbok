//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "Vec4.h"
#include "Angle.h"

constexpr Vec3F RGB(float red, float green, float blue)
{
	return Vec3F(red  ,
							 green,
							 blue );
};

constexpr Vec4F RGB(float red, float green, float blue, float alpha)
{
	return Vec4F(red  ,
							 green,
							 blue ,
							 alpha);
};

Vec3F HCL(Angle hue, float chroma, float luma);

Vec4F      Int2Color(u_int32_t hex);
u_int32_t  Color2Int(Vec4F clr);

Vec3F Lab2RGB(Vec3F lab);
Vec3F RGB2Lab(Vec3F rgb);

Vec4F Lab2RGB(Vec4F laba);
Vec4F RGB2Lab(Vec4F rgba);

constexpr Vec3F RefWhiteD65 = {0.950470, 1.000000, 1.088830}; // CIE standard illuminant D65

namespace Colors
{
	static constexpr Vec3F White = RGB(1, 1, 1);
	static constexpr Vec3F Black = RGB(0, 0, 0);
	
	static constexpr Vec3F Red   = RGB(1, 0, 0);
	static constexpr Vec3F Green = RGB(0, 1, 0);
	static constexpr Vec3F Blue  = RGB(0, 0, 1);
	
	static constexpr Vec4F Transparent = Vec4F(White, 0.0f);
	static constexpr Vec4F Opaque      = Vec4F(White, 1.0f);
};
