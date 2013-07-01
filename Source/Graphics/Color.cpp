// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#include "Color.h"
#include <Math/Operations.h>

ColorRGB ColorRGB::blend(const ColorRGB& other, float factor)
{
	return ColorRGB(Red * (1 - factor) + other.Red * factor, Green * (1 - factor) + other.Green * factor, Blue * (1 - factor) + other.Blue * factor).clip();
}

ColorRGB ColorRGB::clip()
{
	return ColorRGB{BoundBy(0.f, Red, 1.f), BoundBy(0.f, Green, 1.f), BoundBy(0.f, Blue, 1.f)};
}

ColorHSY::operator ColorRGB()
{	
	float ma[3] = {+1.0000, +1.0000, +1.0000};
	float mb[3] = {+0.7010, -0.2990, -0.2990};
	float mc[3] = {+0.2731, -0.3043, +0.8504};
	float chroma, c1, c2;
	ColorRGB saturated;
	RGBColor unsaturated={Luma, Luma, Luma};
	
	float lumaMatch = (1 - Saturation) * Luma;
	
	chroma = (1.7320508 * Saturation) / fmod(-(float(Hue) / 6 * PI), 1.f);
	c1 =  chroma * Cos(Hue);
	c2 = -chroma * Sin(Hue);
	
	saturated.Red   = ma[0] * Luma + mb[0] * c1 + mc[0] * c2;
	saturated.Green = ma[1] * Luma + mb[1] * c1 + mc[1] * c2;
	saturated.Blue  = ma[2] * Luma + mb[2] * c1 + mc[2] * c2;
	return unsaturated.blend(saturated, Saturation).clip();
}

ColorHSY ColorHSY::tint(const ColorHSY& other)
{
	return {Hue + other.Hue, BoundBy(0.f, Saturation * other.Saturation, 1.f), BoundBy(0.f, Luma * other.Luma, 1.f) };
}